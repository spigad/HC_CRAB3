import types

class BaseHCModel:

  def attrToDict(self):
    attrs = self.__dict__
    for k,v in attrs.items():
      
      if isinstance(v,types.ListType):
        subattrs = []  
        for subv in v:
          deepToDict = getattr(subv,'attrToDict','')
          if deepToDict:
            subattrs.append(deepToDict())
          else:
            subattrs.append(subv)   
        attrs[k] = subattrs
        
      else:  
        deepToDict = getattr(v,'attrToDict','')
        if deepToDict:
          attrs[k] = deepToDict()    
    
    return attrs

#  def objToDict(self):
#      
#    obj = {}
#    obj[self.type] = self.attrToDict()
#        
#    return obj          