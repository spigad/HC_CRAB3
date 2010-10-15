#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

# Define the rules for cloning when there are inlines associated. 

INLINES = {
            'Template': ('template',['TemplateBackend','TemplateCloud','TemplateDspattern','TemplateHost','TemplateSite','TemplateUser']),
            'Test'    : ('test',['TestBackend','TestCloud','TestDspattern','TestHost','TestSite','TestUser']),
          }


#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

#Define the rules for cloning any object, except the ones with M2M relations.
#Not supported yet.

RULES = {
          'Template': 
            {
              'active':'setZero',
            },
          'Test':   
            {
              'state':'setState',
              'version':'setVersion',
              'cloned':'setCloned',    
            },
        }

def setZero(self):
  return 0

def setState(self):
  return 'draft'

def setVersion(self):
  return 4

def setCloned(self):
  if self:
    return self+1
  else:
    return 1
