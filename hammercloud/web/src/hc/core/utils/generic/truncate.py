"""Implements functions to truncate list of strings (such as site names)."""


def truncateList(lst, top):
    """"Filter for the use in templates

    Filter for the Django template system date given a list of object
    and a number n return the first n elements joined by ', '.
    If the list is longer than n it appends in the end ', x more...'
    where x is the number of left elements.
    """
    string = ', '.join(map(str, lst[:top]))
    if len(lst) > top:
        string += ', %d more...' % (len(lst) - top)
    return string


def truncateString(string, max_len):
    """Filter for the use in templates.

    This is a version which trimms out the right part of the string.
    """
    if len(string) > max_len:
        string = str(string[:max_len]) + '...'
    return string
