help_msg = ''' WELCOME to the HammerCloud help.
There is only one method you can invoke, get(model,actions,conditions)

With this method you specify which table you want to query (model),
what do you want from your query,
and how do you want to do the query (conditions).

Model: 
  Only one will survive... Only one at a time.
  o Result: get the values used to compose the plots, lists and timelines.
  o Site: curious about the sites. Use this to satisfy your information hunger.
  o Test: all information related with the test setup.
  o Template: same here, but with templates.
  
Actions:
  As many as you want, but not every action is applicable with every model.
  o COMMON ACTIONS:
    + Aggregate: filter with the intersection of all conditions. This is false by
      default.
    + Info : obvious, isn't it ?
    + Number : how many ?
  o MODEL DEPENDENT ACTIONS:
    + Result:
    + Site:
      - id:
      - name:
      - alternate_name:
      - description:
      - cloud:
      - backend:
      - ddm:
      - enabled:
      - queue:
    + Test:
      - id:
      - starttime:
      - endtime:
      - description:
      - jobtemplate:
      - usercode:
      - optionfile:
      - inputtype:
      - testoption:
      - gangabin:
      - extraargs:
      - template:
      
    + Template:     
  
  

'''
