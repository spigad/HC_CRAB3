class DicConfig:

  def __init__(self,dic):
    for k,v in dic.items():
      setattr(self,k,v)


