"""Offers a dictionary-like class to store configurations."""


class DicConfig(object):
    """Class to store config values as attributes."""

    def __init__(self, dic):
        """Copies the values from the dict to attributes of this class."""
        super(DicConfig, self).__init__()
        for k, v in dic.iteritems():
            setattr(self, k, v)
