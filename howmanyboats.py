def howmanyboats_using_hash(people, limit):
    hashmap = {} #space o(n)
    # loop(o(n))
    boats = 0
    # import pdb; pdb.set_trace()
    for i in range(len(people)):
        if people[i] == limit:
            boats +=1
        else:
            if (people[i]) in hashmap:
                hashmap[people[i]] -=1
                if (hashmap[people[i]] == 0):
                    hashmap.pop(people[i])
                boats +=1    
            else:
                if limit-people[i] not in hashmap:
                    hashmap[limit-people[i]] = 1  
                else:
                    hashmap[limit-people[i]] += 1             

    return boats + len(hashmap)

print(howmanyboats_using_hash([3,2,2,1], 3))
print(howmanyboats_using_hash([3,2,2,1], 4))

def howmanyboats_using_2ptrs(people, limit):
    left =0
    right = len(people)-1
    boats = 0
    people.sort() # sort the array ==> o(nlogn) time, o(n) complexity
    # below loop o(n) , So, o(nlogn) + o(n) ==> o(nlogn)
    #import pdb; pdb.set_trace()
    while (right >= left):

        if (people[left] + people[right]) <= limit:
            left += 1
            right -=1
        else:
            right -=1

        boats +=1

    return boats
        
print(howmanyboats_using_2ptrs([3,2,2,1], 3))
print(howmanyboats_using_2ptrs([3,2,2,1], 4))
