Job(
  application = DaVinci(
    version = 'v26r1',
    platform = 'x86_64-slc5-gcc43-opt',
    optsfile = [File('####_OPTSFILE_####')]
    ),
  splitter = DiracSplitter(
    filesPerJob = 2,
    maxFiles = 2,
    ignoremissing = True
    ),
  backend = Dirac(),
  inputdata = BKQuery('####_PATTERN_####').getDataset(),
  outputdata = ['b2hh_stripped.root'],
  name = 'HammerCloud'
)

