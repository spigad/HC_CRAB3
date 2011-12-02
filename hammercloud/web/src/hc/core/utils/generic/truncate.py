def truncateList(list,top):
    '''
    Filter for the Django template system date given a list of object
    and a number n return the first n elements joined by ', '.
    If the list is longer than n it appends in the end ', x more...'
    where x is the number of left elements.
    '''

    string = ', '.join(map(str, list[:top]))
    if len(list) > top:
      string += ', %d more...'%(len(list)-top)
    return string

def truncateString(string,max):

    if len(string) > max:
      string = str(string[:max])+'....'
    return string
