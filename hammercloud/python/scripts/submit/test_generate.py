class TestGenerate():

  def run(self,dic):
    app = dic['-a']
    if app == 'core':
      print '[ERROR][%s][test_generate] not available at core app.'%(app)
      return 1

    if not dic.has_key('-t'):
      print '[ERROR][%s][test_generate] Test ID missing.'%(app)
      return 1

    print 'To be continued.'
