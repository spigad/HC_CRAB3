
'''Singleton metaclass that allows to redefine the creation of instances.'''

class Singleton(type):
    '''Allows to use objects normally while they are singletons.'''

    def __init__(mcs, name, bases, dic):
        '''Initializes the metaclass.'''
        mcs.__instance = None
        type.__init__(mcs, name, bases, dic)

    def __call__(mcs, *args, **kwargs):
        '''Redefines the instance creator for the class.'''
        if mcs.__instance is None or type(mcs.__instance) != mcs:
            mcs.__instance = type.__call__(mcs, *args, **kwargs)
        return mcs.__instance
