class Node:
    def __init__(self, val):
        self.value = val 
        self.next:Node  = None

class LinkedList:
    def __init__(self):
        self.root:Node = None
    
    def addNode(self, val):
        import pdb; pdb.set_trace()
        node = Node(val)
        if not self.root:
            self.root = node
        else:
            temp:Node = self.root
            while(temp.next):
                temp=temp.next
            
            temp.next = node


    def traverse(self):
        if self.root == None:
            # raise "NoElements in List"
            print("No Elements in the list")
        temp:Node = self.root
        while(temp):
            print(temp.value, " --> ", end =" ")
            temp = temp.next
        print(" NULL ")

    def remove(self, val):
        if self.root == None:
            raise "NoElements in List"
        if self.root.value == val:
           self.root = None
        else:
            temp:Node = self.root
            while(temp.next):
                if temp.next.value == val:
                    break
                temp = temp.next
            
            temp.next = temp.next.next
    

link = LinkedList()
link.traverse()
link.addNode(1)
link.addNode(2)
link.addNode(3)
link.traverse()
link.remove(2)
link.traverse()
