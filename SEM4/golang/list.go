package main

import (
	"fmt"
)

type node struct {
	data byte
	prev, next *node
}

type linkedList struct {
	len int
	tail, head *node
}

func initList() *linkedList {
	return &linkedList{}
}

func (list *linkedList) lengthList() int{
	return list.len
}

func (list *linkedList) appendList(data byte) {
	newNode := &node{
		data: data,
	}
	if list.head == nil {
		list.head = newNode
		list.tail = newNode
	} else {
		tempNode := list.head
		for tempNode.next != nil {
			tempNode = tempNode.next
		}
		newNode.prev = tempNode
		tempNode.next = newNode
		list.tail = newNode
	}
	list.len++
	return
}

func (list *linkedList) insert(data byte, idx int) {
	newNode := &node{
		data: data,
	}
	newNode.next = nil;
	newNode.prev = nil;

	if list.len == 1 || idx > list.len + 1 {
		return list.appendList(newNode)
	}
	
	if idx < 1 {
		fmt.Println("Invalid position!")
		return
	} else {
		temp := list.head;
		for i := 1; i < idx-1; i++ {
			if temp != nil {
				temp = temp.next;
			}
		}
		if temp != nil {
			newNode.next = temp.next;
			newNode.prev = temp;
			temp.next = newNode;
			if newNode.next != nil {
				newNode.next.prev = newNode; 
			} 
		} else {
			fmt.Println("The previous node is null.");
		} 
	}
	list.len++
	return
}

func (list *linkedList) delete(idx int) value byte {
	if idx < 1 {
		fmt.Println("Invalid index to delete")
		return
	}
	if list.head == nil {
		fmt.Println("Empty linked list")
		return
	}
	if idx == 1 {
		list.head = list.head.next
		if list.head != nil {
			list.head.prev = nil
		} else {
			list.tail = nil
		}
		value = list.head.value
	} else {
		temp := list.head
		n := 1
		for temp != nil && n < idx {
			temp = temp.next
			n++
		}
		if temp == nil {
			fmt.Println("Node index to delete greater than list size")
		} else {
			temp.prev.next = temp.next
			if temp.next != nil {
				temp.next.prev = temp.prev
			} else {
				list.tail = temp.prev
			}
			value = temp.value
		}
	}
	list.len--
	return value
}

func (list *linkedList) deleteAll(element byte) {
	if list.head == nil {
		fmt.Println("Empty linked list")
	} else {
		temp := list.head
		found := bool false
		for temp != nil {
			if temp.data == element {
				found = true
				if temp == list.head {
					list.head = list.head.next
					if list.head == nil {
						list.tail = nil
					} else {
						list.head.prev = nil
					} 
					list.len--
				} else {
					temp.prev.next = temp.next
					if temp.next == nil {
						list.tail = temp.prev
					} else {
						temp.next.prev = temp.prev
					}
					list.len--
				}
			}
			temp = temp.next
		}
		if !found {
			fmt.Println("Element not found")
		}
	}
}

func (list *linkedList) get(idx int) byte {
    temp := list.head
	pos := 0

    for pos != idx && temp.next != nil {
        pos++
        temp = temp.next
    }

    if temp.data != nil {
        return temp.data
	}
    return nil
}

func (list *linkedList) clone() *linkedList {
	clone := initList()
	tempNode := list.head
	for i := 0; i < list.len; i++ {
		clone.append(tempNode.data)
		tempNode = tempNode.next
	}
	return clone
}

func (list *linkedList) reverse() {
	tempNode := list.head
    var nextInList *node
    list.head, list.tail = list.tail, list.head
    for tempNode != nil {
        nextInList = tempNode.next
        tempNode.next, tempNode.prev = tempNode.prev, tempNode.next
        tempNode = nextInList
    }
}

func (list *linkedList) findFirst(element byte) int {
	tempNode := list.head
	for i := 0; i < list.len; i++ {
		if tempNode.data == element { 
			return i
		}
		tempNode = tempNode.next
	}
	return -1
}

func (list *linkedList) findLast(element byte) int {
	tempNode := list.tail
	for i := list.len; i > 0; i-- {
		if tempNode.data == element { 
			return i
		}
		tempNode = tempNode.prev
	}
	return -1
}

func (list *linkedList) clear() {

}

func (list *linkedList) extend(elements) {

}

func main() {
	list := initList()
}

//Unfinished implementation of linked list