from GChartWrapper import *
from math import ceil,floor
import numpy

def line(values, labels, legend, title, colors=['0000FF']):

    if not values:
      return None

    chart = Line(values)
    chart.title(title)
    chart.label(*labels)
    chart.legend(*legend)
    chart.color(*colors)
    chart.size(400,250)
    chart.margin(0,0,30,0)
    chart.axes.type('y')
    max_y = max(max(values[0]),max(values[1]))*1.1
    chart.axes.range(0,0,max_y,int(max_y/10))
    chart.scale(0,max_y,0,max_y)
    return str(chart)


def pie(values, labels, title, colors=['333333']):
    if not values:
        return None
    sumvalues = sum(values)
    values = [x*100/sumvalues for x in values]
    chart = Pie(values)
#    chart.size(300,225)   
    chart.size(300,225)
    chart.title(title)
    chart.label(*labels)
    chart.color(*colors)
    return str(chart)

def hist(x, bins, xlabel, title, x_range=None, mean_func=None):

    x_sub = []
    for k in x:
      if k != None:
        x_sub += [float(k)]
#    x = [float(k) for k in x]
    x = x_sub
    if not x:
        return None
    if mean_func is None:
        mean_func = numpy.mean
    mean = mean_func(x)
    std = numpy.std(x)
    chart = Histogram(x,bins,x_range, mean_func)
    chart.size(300,300)
    chart.color('4d89f9')
    chart.axes.type('xyxx')
    chart.axes.range(0,
                     chart.get_x_range()[0],
                     chart.get_x_range()[1],
                     ((chart.get_x_range()[1]-chart.get_x_range()[0])/min(bins,8)))
    ylim = ceil(chart.get_max())
    chart.axes.range(1,0,ylim,ylim/10)
    chart.scale(0,ylim)
    chart.title(title)
    chart.axes.position(2,50.0)
    chart.axes.label(2,xlabel)
    chart.axes.position(3,80.0)
    chart.axes.label(3,'mean=%s dev=%s'%(round(mean,1),round(std,1)))
    return str(chart)

class Histogram(VerticalBarGroup):
   
  def __init__(self, data, bins, x_range=None, mean_func=numpy.mean, **kwargs):
    a = float(min(data))
    b = float(max(data))
    s = float(numpy.std(data))
    m = float(mean_func(data))
    if not x_range:
      if a < 0:
          x_range = (a - 0.1 * (b - a), b + 0.1 * (b - a))
      elif a == 0:
          x_range = (0.0, 1.1 * b)
      else:
          if m / s > 10:
              x_range = (a - 0.1 * (b - a), b + 0.1 * (b - a))
          else:
              x_range = (0.0, b + 0.1 * (b - a))
    assert x_range is not None
    assert x_range[0] <= x_range[1]
    assert bins > 0
    bin_width = (x_range[1] - x_range[0]) / bins
    val = dict()
    for i in xrange(bins):
      val[i+1] = 0
    for k in data:
      bin_index = int(ceil(((k - x_range[0]) / bin_width)))
      if bin_index > bins:
          bin_index = bins
      elif bin_index < 1:
          bin_index = 1
      val[bin_index] += 1
    self.max_value = max(val.values())
    self.bar('a',1,1)
    self.x_range = x_range
    VerticalBarGroup.__init__(self, val.values(), **kwargs)

  def get_x_range(self):
    return self.x_range

  def get_max(self):
    return self.max_value
