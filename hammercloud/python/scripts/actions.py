from scripts.server import create_functional_tests
from scripts.submit import register_host,create_at_job,test_generate,test_submit

class CronActions:

  def create_functional_tests(self,dic):
    cft = create_functional_tests.CreateFunctionalTests()
    cft.run(dic)

  def register_host(self,dic):
    rh = register_host.RegisterHost()
    rh.run(dic)

  def create_at_job(self,dic):
    caj = create_at_job.CreateAtJob()
    caj.run(dic)

  def test_generate(self,dic):
    tg = test_generate.TestGenerate()
    tg.run(dic)

  def test_submit(self,dic):
    ts = test_submit.TestSubmit()
    ts.run(dic)
