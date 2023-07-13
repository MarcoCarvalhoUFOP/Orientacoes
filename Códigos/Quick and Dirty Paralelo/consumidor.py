import thread
from recurso import *
from threading import *

class Consumidor(Thread):
	def __init__(self, recurso):
		Thread.__init__(self)
		self.recurso = recurso

	def consome(self, item):
		pass

	def run(self):
		while not self.recurso.isOver() or not self.recurso.isEmpty():
			item = self.recurso.pop()
			if item == 'fim':
				return
			self.consome(item)