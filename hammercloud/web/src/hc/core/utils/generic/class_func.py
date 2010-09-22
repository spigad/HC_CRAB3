#Method that returns an instance of the class specified
def custom_import(name):
 
  parts = name.split('.')
  module = ".".join(parts[:-1])
  m = __import__( module )
  for comp in parts[1:]:
    m = getattr(m, comp)
  return m

