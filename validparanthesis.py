def isValid(s) -> bool:
    # import pdb; pdb.set_trace()
    #Use stack when you find a open paranthesis or curly or angle bracket.
    # look for its equivalent
    stack  = []
    hash = { '}':'{', ")":"(", "]":"["}
    for item in s:
        if item in hash: #check the items should any one of the combo
            if stack and stack[-1] == hash[item]:
                #check if the item in stack and pop it
                stack.pop()
            else:
                return False
        else:
            #append the item, if not in hash
            stack.append(item)
    return True if not stack else False
    
print(isValid("()"))
print(isValid("()[]{}"))
print(isValid("(]"))
