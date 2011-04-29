Job (
 application = PandaPilot () ,
 splitter = GenericSplitter (
    attribute = 'application.queue' ,
    values = [####SITES#### for x in xrange(10)] 
    ) ,
 backend = LCG (
    requirements = AtlasLCGRequirements (
       walltime = 1440 
       )
    )
) 

