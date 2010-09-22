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
              'version':'setVersion',
              'cloned':'setCloned',    
            },
        }

def setZero(self):
  return 0

def setVersion(self):
  return 4

def setCloned(self):
  return self+1
