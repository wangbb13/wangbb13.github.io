# -*- coding: utf-8 -*- 
from multiprocessing import Pipe, Queue, Value, Array, Process
import multiprocessing.connection.Connection as PType
import multiprocessing.queues.Queue as QType
import multiprocessing.sharedctypes.Synchronized as VType
import multiprocessing.sharedctypes.SynchronizedArray as AType

class ConnTools(object):
  '''
  collecton of communication tools:
  '''
  def __init__(self, pipe, queue, value, array):
    assert isinstance(pipe, PType)
    assert isinstance(queue, QType)
    assert isinstance(value, VType)
    assert isinstance(array, AType)
    self.pipe  = pipe
    self.queue = queue
    self.value = value 
    self.array = array

