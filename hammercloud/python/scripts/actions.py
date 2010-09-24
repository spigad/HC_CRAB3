from scripts.server import create_functional_tests
from scripts.submit import register_host,create_at_job,test_generate,test_submit#,test_report

class CronActions:

  def create_functional_tests(self,app,dic):
    cft = create_functional_tests.CreateFunctionalTests()
    cft.run(app,dic)

  def register_host(self,app,dic):
    rh = register_host.RegisterHost()
    rh.run(app,dic)

  def create_at_job(self,app,dic):
    caj = create_at_job.CreateAtJob()
    caj.run(app,dic)

  def test_generate(self,app,dic):
    tg = test_generate.TestGenerate()
    tg.run(app,dic)

  def test_submit(self,app,dic):
    ts = test_submit.TestSubmit()
    ts.run(app,dic)

  def test_report(self,app,dic):
    pass
#    tr = test_report.TestReport()
#    tr.run(dic)
