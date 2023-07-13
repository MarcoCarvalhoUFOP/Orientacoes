from collections import deque

class Recurso():
	def __init__(self, cond):
		self.recurso = deque([])
		self.cond = cond
		self.tam = 0
		self.fim = False

	def push(self, item):
		self.cond.acquire()
		self.recurso.append(item)
		self.tam = self.tam+1
		self.cond.notifyAll()
		self.cond.release()

	def pop(self):
		self.cond.acquire()
		while self.isEmpty():
			if self.isOver():
				self.cond.notifyAll()
				self.cond.release()
				return 'fim'
			self.cond.wait()
		item = self.recurso.popleft()
		self.tam = self.tam-1
		self.cond.notifyAll()
		self.cond.release()
		return item
		
	def size(self):
		return self.tam
		
	def isEmpty(self):
		return self.tam == 0
		
	def isOver(self):
		return self.fim
		
	def over(self):
		self.fim = True
		self.cond.acquire()
		self.cond.notifyAll()
		self.cond.release()