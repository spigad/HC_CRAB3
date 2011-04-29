Job(
  application = Gauss(
    version = 'v39r2',
    optsfile = [File('####_OPTSFILE_####')]
    ),
  splitter = GaussSplitter(
    numberOfJobs = 10,
    eventsPerJob = 50
    ),
  merger = None,
  backend = Dirac(
    settings = {'Destination':'####_SITE_####'}
  ),
  inputsandbox = [],
  name = 'HammerCloud'
)

