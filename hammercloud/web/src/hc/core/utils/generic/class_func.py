"""Custom import mechanism for Python objects by name."""

# TODO(rmedrano): Remove the dependency on this kind of imports.


def custom_import(name, value=None):
    """Given the name of a class or function, imports it.

    Arguments:
    name -- Name of the object to import.
    value -- Default value to return in case import fails.

    Returns: the module object or the default value in case of failure.
    """
    try:
        parts = name.split('.')
        module = ".".join(parts[:-1])
        m = __import__(module)
        for comp in parts[1:]:
            m = getattr(m, comp)
        return m
    except:
        return value
