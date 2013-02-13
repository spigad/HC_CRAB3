"""Custom import mechanism for Python objects by name."""

# TODO(rmedrano): Remove the dependency on this kind of imports.


def custom_import(name):
    """Given the full name of a class or function, imports it in depth.

    Arguments:
    name -- Name of the object to import, must be complete.

    Returns: the module object or the default value in case of failure.
    """
    try:
        parts = name.split('.')
        module = '.'.join(parts[:-1])
        m = __import__(module)
        for comp in parts[1:]:
            m = getattr(m, comp)
        return m
    except (ValueError, AttributeError):
        raise ImportError('No object named %s' % name)
