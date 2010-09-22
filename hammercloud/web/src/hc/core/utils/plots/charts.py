from GChartWrapper import *
from math import ceil
import numpy

def pie(values, labels, title, colors=['0000FF']):
    if not values:
        return None
    sumvalues = sum(values)
    values = [x*100/sumvalues for x in values]
#    chart = Pie3D(values)
#    chart.size(300,150)
    chart = Pie(values)
    chart.size(300,225)
    chart.title(title)
    chart.label(*labels)
    chart.color(*colors)
    return str(chart)

def hist(x, bins, xlabel, title, x_range=None):

    x_sub = []
    for k in x:
      if k != None:
        x_sub += [float(k)]
#    x = [float(k) for k in x]
    x = x_sub

    if not x:
        return None
    if not x_range:
        x_range = (0,int(max(1,ceil(max(x)*0.1)*10)))
    
    mean = numpy.mean(x)
    std = numpy.std(x)
    chart = Histogram(x,bins,x_range)
    chart.size(300,300)
    chart.color('4d89f9')
    chart.axes.type('xyxx')
    chart.axes.range(0,x_range[0],x_range[1],ceil(((x_range[1]-x_range[0])/min(bins,8))/10)*10)
    ylim = max(40,ceil((chart.get_max()*0.11))*10)
    chart.axes.range(1,0,ylim,ylim/10)
    chart.scale(0,ylim)
    chart.title(title)
    chart.axes.position(2,50.0)
    chart.axes.label(2,xlabel)
    chart.axes.position(3,80.0)
    chart.axes.label(3,'mean=%s dev=%s'%(round(mean,1),round(std,1)))
    return str(chart)

class Histogram(VerticalBarGroup):
   
  def __init__(self, data, bins, x_range=None, **kwargs):
    if not x_range:
      x_range = (0,ceil(max(data)/10)*10)
    val = dict()
    for i in xrange(bins):
      val[i+1] = 0
    for k in data:
      val[max(1,int(ceil(min(k,x_range[1]) / (float(x_range[1]) / bins))))] += 1
    self.max_value = max(val.values())
    self.bar('a',1,1)
    VerticalBarGroup.__init__(self, val.values(), **kwargs)      
       
  def get_max(self):
    return self.max_value
