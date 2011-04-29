from Gaudi.Configuration import *

from Configurables import GaudiSequencer, DaVinci, CondDB, CondDBAccessSvc, DecayTreeTuple, TupleToolTrigger, EventTuple, TupleToolTrigger, LoKi__Hybrid__TupleTool, CombineParticles, GetIntegratedLuminosity, CombineParticles



from Configurables import COOLConfSvc

def disableLFC():

        COOLConfSvc(UseLFCReplicaSvc = False)

appendPostConfigAction(disableLFC)





LoKiTool = LoKi__Hybrid__TupleTool('LoKiTool')

preseltuple = DecayTreeTuple("TuplePreSelB2HH")

preseltuple.InputLocations = [ "/Event/Bhadron/Phys/PreselB2Charged2Body" ]

preseltuple.ToolList +=  [ "TupleToolKinematic"

                           ,"TupleToolGeometry"

                           ,"TupleToolPid"

                           ,"TupleToolPrimaries"

                           ,"TupleToolPropertime"

                           ,"TupleToolTrackInfo"

                           ,"TupleToolEventInfo"

                           ,"LoKi::Hybrid::TupleTool/LoKiTool"

                           ,"TupleToolTrigger"

                           ,"TupleToolRecoStats"

                           ]



preseltuple.addTool(TupleToolTrigger())

preseltuple.TupleToolTrigger.Verbose = True

preseltuple.TupleToolTrigger.VerboseL0 = True

#preseltuple.TupleToolTrigger.VerboseHlt1 = True

#preseltuple.TupleToolTrigger.VerboseHlt2 = True

preseltuple.TupleToolTrigger.TriggerList = ['L0'

                                            #,'Hlt1DiHadronDecision'

                                            #,'Hlt2B2HHDecision'

                                            #,'Hlt2B2HHLTUnbiasedDecision'

                                            ]

preseltuple.addTool(LoKiTool)

preseltuple.LoKiTool.Variables = {

    "RichPIDk" : "PPINFO(LHCb.ProtoParticle.RichDLLk,-1000)"

    ,"RichPIDp" : "PPINFO(LHCb.ProtoParticle.RichDLLp,-1000)"

    ,"DOCA" : "DOCAMAX"

    ,"MKK": "WM('K+','K-')"

    ,"MKPi": "WM('K+','pi-')"

    ,"MPiK": "WM('pi+','K-')"

    ,"MPPi": "WM('p+','pi-')"

    ,"MPiP": "WM('pi+','p~-')"

    ,"MPK": "WM('p+','K-')"

    ,"MKP": "WM('K+','p~-')"

    }



preseltuple.Decay = "B0 -> ^pi+ ^pi-"

preseltuple.TupleName = "PreSelB2HH"



evttuple = EventTuple("EventInfo")

evttuple.ToolList +=  [ "TupleToolEventInfo"

                        ,"TupleToolTrigger"

                        ]



evttuple.addTool(TupleToolTrigger())

evttuple.TupleToolTrigger.Verbose = True

evttuple.TupleToolTrigger.VerboseL0 = True

#evttuple.TupleToolTrigger.VerboseHlt1 = True

#evttuple.TupleToolTrigger.VerboseHlt2 = True

evttuple.TupleToolTrigger.TriggerList = ['L0'

                                         #,'Hlt1DiHadronDecision'

                                         #,'Hlt2B2HHDecision'

                                         #,'Hlt2B2HHLTUnbiasedDecision'

                                         ]

#evttuple.TupleToolTrigger.CollateTriggerList = True



evttuple.addTool(LoKiTool)

evttuple.TupleName = "EventInfo"



dv = DaVinci()

dv.DataType = "2010"

dv.Simulation = False

dv.EvtMax     = -1

dv.TupleFile  = 'b2hh_stripped.root'

dv.PrintFreq  = 100

condDB = CondDB()

condDB.UseOracle = True



dv.DDDBtag = "head-20100518"

dv.CondDBtag = "head-20100715"

dv.Lumi = True

dv.WriteFSR = True

dv.UserAlgorithms = [ evttuple, preseltuple ]



