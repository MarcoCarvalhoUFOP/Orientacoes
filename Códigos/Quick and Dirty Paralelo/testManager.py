# -*- coding: utf8 -*-

from recurso import *
from produtor import *
from consumidor import *
from threading import *
from os import system, listdir
from os.path import isfile, join
from pprint import pprint
from random import randint
import operator
import re
import subprocess

def available_cpu_count():
    """ Number of available virtual or physical CPUs on this system, i.e.
    user/real as output by time(1) when called with an optimally scaling
    userspace-only program"""

    # cpuset
    # cpuset may restrict the number of *available* processors
    try:
        m = re.search(r'(?m)^Cpus_allowed:\s*(.*)$',
                      open('/proc/self/status').read())
        if m:
            res = bin(int(m.group(1).replace(',', ''), 16)).count('1')
            if res > 0:
                return res
    except IOError:
        pass

    # Python 2.6+
    try:
        import multiprocessing
        return multiprocessing.cpu_count()
    except (ImportError, NotImplementedError):
        pass

    # http://code.google.com/p/psutil/
    try:
        import psutil
        return psutil.cpu_count()   # psutil.NUM_CPUS on old versions
    except (ImportError, AttributeError):
        pass

    # POSIX
    try:
        res = int(os.sysconf('SC_NPROCESSORS_ONLN'))

        if res > 0:
            return res
    except (AttributeError, ValueError):
        pass

    # Windows
    try:
        res = int(os.environ['NUMBER_OF_PROCESSORS'])

        if res > 0:
            return res
    except (KeyError, ValueError):
        pass

    # Linux
    try:
        res = open('/proc/cpuinfo').read().count('processor\t:')

        if res > 0:
            return res
    except IOError:
        pass

    # Other UNIXes (heuristic)
    try:
        try:
            dmesg = open('/var/run/dmesg.boot').read()
        except IOError:
            dmesgProcess = subprocess.Popen(['dmesg'], stdout=subprocess.PIPE)
            dmesg = dmesgProcess.communicate()[0]

        res = 0
        while '\ncpu' + str(res) + ':' in dmesg:
            res += 1

        if res > 0:
            return res
    except OSError:
        pass

    raise Exception('Can not determine number of CPUs on this system')

import socket

num_cons   = available_cpu_count()	# Executa o metodo paralelamente para varias instancias
num_prod   = 1						# Le do arquivo que contem as instancias
f          = 'index.txt'			# Arquivo que contem as instancias
caminho	   = './instances'	        # Caminho de onde as instancias serao salvas
cmd        = './main'				# Comando que executa o codigo em C/C++
runs	   = 20						# Numero de runs
computador = socket.gethostname()	# Nome do computador onde foram executados os testes
metodo	   = 1						# Caso haja mais de um metodo qual deve ser executado
metodos	   = {						# Nome dos metodos para colocar no arquivo de resumo dos resultados
	1:'DFS',
	2:'BFS',
	3:'Aleatorio',
	4:'Guloso'
}

class ConsumidorExt(Consumidor):
	def __init__(self, rec):
		Consumidor.__init__(self, rec)

	def consome(self, item):
		arquivo = item[1]
		run 	= str(item[0])
		rand	= str(item[2])
		system(cmd + ' ' + arquivo + ' ' + run + ' ' + str(metodo) + ' ' + rand)

class ProdutorExt(Produtor):
	def __init__(self, rec, arquivo):
		Produtor.__init__(self, rec)
		self.arquivo = open(arquivo, 'r')
		self.rand = [100030001, 108767801, 118626811, 132010231, 152505251, 174595471, 304090403, 317252713, 317252713, 349575943, 385636583, 704585407, 736525637, 757686757, 912161219, 934656439, 963868369, 999727999, 764838467, 388575883]

	def produz(self):
		for line in self.arquivo:
			for i in range(runs):
				rec.push((i, line.rstrip(), self.rand[i]))

cond = Condition()
rec = Recurso(cond)

p = ProdutorExt(rec, f)
p.start()

cons = []
for i in range(num_cons):
	cons.append(ConsumidorExt(rec))

for c in cons:
	c.start()

p.join()
rec.over()

for c in cons:
	c.join()

results = {}

for f in listdir(caminho):
	if isfile(join(caminho, f)):
		aux = open(join(caminho, f), 'r')
		v = aux.readline().rstrip().split('|')
		if v[0] in results:
			results[v[0]]['run'].append(int(v[1]))
			results[v[0]]['custo'].append(v[2])
			results[v[0]]['tempo'].append(float(v[3]))
		else:
			results[v[0]] = {
				'run':[int(v[1])],
				'custo':[v[2]],
				'tempo':[float(v[3])]
			}

f = open('./results/RESULT_SUMMARY.txt', 'w')

f.write('Computador=' + computador + '\n')
f.write('Metodo=' + metodos[metodo] + '\n')
f.write('Runs=' + str(runs) + '\n')
m = len(max(results, key=len))

f.write('{:<{}s} {:>4} {:>9} {}\n'.format('Problema', m, 'Run', 'Custo', 'Tempo'))

sorted_results = sorted(results.items(), key=operator.itemgetter(0))

for r in sorted_results:
    for pos in range(runs):
        f.write('{:<{}s} {:>4} {:>9} {}\n'.format(r[0], m, r[1]['run'][pos], custo, tempo))

# Result Summary para rodar conjunto de instâncias apenas uma vez, ou seja, multirun = 1
i = 0
cost_acum = 0
time_acum = 0

for r in sorted_results:
    i = i + 1

    cost_acum = cost_acum + float(r[1]['custo'][0])
    cost_acum = cost_acum + float(r[1]['tempo'][0])

# para facilitar o copy and paste na tabela de estatisticas, os separadores de decimal pontos(.) são substituidos por vírgulas(,)
    custo = str(r[1]['custo'][0])
    custo = custo.replace(".",",")

    tempo = str(r[1]['tempo'][0])
    tempo = tempo.replace(".", ",")


    f.write('{:<{}s} {:>4} {:>9} {}\n'.format(r[0], m, r[1]['run'][0], custo, tempo))

# Ao final do arquivo, são printados os acumuladores do custo e do tempo.
# Util quando o autor de outro artigo possui tabelas de resultados de CONJUNTOS de instâncias.
cost_acum = cost_acum/i
time_acum = time_acum/i
f.write('{} {}'.format(cost_acum, time_acum))


# Result Summary para multirun.
bestfile = open('./results/best.txt', 'w')
best = 2000
bestTime = 500000
eachRun = 0

i = 0
custao = 0
tempao = 0

for r in sorted_results:
    for pos in range(runs):
        i = i + 1
        custao = custao + float(r[1]['custo'][pos])
        tempao = tempao + float(r[1]['tempo'][pos])
        

        if float(r[1]['custo'][pos]) < best:
            best = float(r[1]['custo'][pos])
            bestTime = float(r[1]['tempo'][pos])
            eachRun = pos+1

        custo = str(r[1]['custo'][pos])
        custo = custo.replace(".",",")

        tempo = str(r[1]['tempo'][pos])
        tempo = tempo.replace(".", ",")

        f.write('{:<{}s} {:>4} {:>9} {}\n'.format(r[0], m, r[1]['run'][pos], custo, tempo))

    best = str(best)
    best = best.replace(".",",")

    bestTime = str(bestTime)
    bestTime = bestTime.replace(".",",")

    bestfile.write('{:<{}s} {} {} {}\n'.format(r[0], m, best, bestTime, eachRun))
    best = 2000
    bestTime = 500000
    eachRun = 0

cost_acum = cost_acum/i
time_acum = time_acum/i
f.write('{} {}'.format(cost_acum, time_acum))