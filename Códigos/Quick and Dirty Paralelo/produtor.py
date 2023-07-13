import thread
from recurso import *
from threading import *

class Produtor(Thread):
    def __init__(self, recurso):
        Thread.__init__(self)
        self.recurso = recurso
        
    def produz(self):
    	pass

    def run(self):
        self.produz()