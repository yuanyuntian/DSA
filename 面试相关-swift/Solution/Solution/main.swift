//
//  main.swift
//  Solution
//
//  Created by CQ on 2023/3/19.
//

import Foundation

/**首先创建一个字典，遍历nums，查询target-num是否存在在字典中，如果不存在，将num作为key，index作为value存入字典中，继续遍历下一个，直到字典中出现key=target-num的组合，当前key对应的value和当前的index就是要找的两个数的位置
 
 hash的作用能除去重复的计算
**/
func twoSum(nums:Array<Int>, target:Int) -> [Int]?{
    var dic = [Int:Int]()
    for (index, value) in nums.enumerated() {
        guard let pairedIndex = dic[target - value] else {
            dic[target - value] = index
            continue
        }
        return [pairedIndex , index]
    }
    return nil
}

/**给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 -1
 使用哈希表存储频数
 
 我们可以对字符串进行两次遍历。

 在第一次遍历时，我们使用哈希映射统计出字符串中每个字符出现的次数。在第二次遍历时，我们只要遍历到了一个只出现一次的字符，那么就返回它的索引，否则在遍历结束后返回 −1
 **/
func firstUniqChar(_ s:String) -> Int {
    var dic = [Character:Int]()
    for c:Character in s {
        guard dic[c] != nil else {
            dic[c] = 1
            continue
        }
        dic[c] = dic[c]! + 1
    }
        
    for (index ,ch) in s.enumerated() {
        if dic[ch] != nil && dic[ch] == 1 {
            return index
        }
    }
    return -1
}


class Solution {
    
    /**
     给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。请你将两个数相加，并以相同形式返回一个表示和的链表。（你可以假设除了数字 0 之外，这两个数都不会以 0 开头。）
     
     在这道题中，首先，提到了逆序存储，我们在做加法运算时，是从个位数开始的，所以在这里我们不需要倒序处理数据存储，但我们要处理的是加法运算中的逢十进一位，也就是进位处理。 其次，这题考察了我们对链表双指针的操作。
     需要注意的就是：

     获取两个链表对应的长度
     对齐相加考虑进位
     在较短的链表末尾补零

     同时在做链表题时，有个技巧就是使用dummy(虚拟头节点)。好处是，不会影响起始节点的操作，如果不理解这个技巧的话，在之后的链表题中它的作用也会不言而喻。
     在这题中，我想到的是使用while循环解法，或者递归解法去实现。

     首先创建一个虚拟的头节点dummy，我们把需要操作的链表都放在这个节点下；
     然后我们需要记录一个进位数，用来在后面运算。
     再然后我们开启一个 while循环，满足条件就是 两个链表都为空，且没有进位时跳出循环。
     在循环内，处理两个链表中值的加法运算，逢十进一，进位给下一次运算的结果叠加。使用运算后的结果生成一个节点，并将操作的指针切换到下一个节点，进行下一个循环
     循环结束后，返回虚拟的头节点下的下一个节点即dummy.next。
          
     */

    class ListNode {
        public var value:Int
        public var next:ListNode?
        public init(value: Int, next: ListNode? = nil) {
            self.value = value
            self.next = next
        }
    }
    
    class func addTwoNumbers(_ l1:ListNode?, _ l2:ListNode?) -> ListNode?{
        var carry = 0
        let dummy = ListNode(value: -1)
        var newNode = dummy
        
        var n1:ListNode? = l1
        var n2: ListNode? = l2
        
        //当两个链表为空，且无进位时（carry  == 0），终止循环
        while n1 != nil || n2 != nil || carry > 0 {
            var val = carry
            
            if let node = n1 {
                val += node.value
                n1 = node.next
            }
            
            if let node = n2 {
                val += node.value
                n2 = node.next
            }
            
            carry  = val / 10
            val = val % 10
            
            newNode.next = ListNode(value: val)
            newNode = newNode.next!
        }
        return dummy.next
    }
}

let a  = twoSum(nums: [1,10,20,1,30,20,100,0,101], target: 101)

let index = firstUniqChar("asbcedacs")

let a0 = Solution.ListNode(value: 1)
let a1 = Solution.ListNode(value: 5)
let a2 = Solution.ListNode(value: 8)
a0.next = a1
a1.next = a2

let b0 = Solution.ListNode(value: 2)
let b1 = Solution.ListNode(value: 8)
let b2 = Solution.ListNode(value: 2)

b0.next = b1
b1.next = b2

let s = Solution.addTwoNumbers(a0, b0)

print("result")

