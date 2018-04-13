# 常见的排序算法

### 快速排序
1. 时间复杂度: 平均 O(nlog<sub>2</sub>n), 最好 O(nlog<sub>2</sub>n) 最坏 O(n<sup>2</sup>)
2. 空间复杂度: O(nlog<sub>2</sub>n)
3. 稳定性: 否
4. 描述: 通过一趟排序将记录按关键字分割为两部分, 两部分分别进行下一轮排序
5. 适用场景: 由于是最快的通用排序算法, 在大多数情况下使用
6. 代码:
```java
public void quickSort(int[] array, int begin, int end){
    if(begin>=end) return;
    int flag = array[begin];
    int i = begin;
    int j = end-1;
    while(i<j){
        while(i<j && flag<=array[j]) j--;
        array[i] = array[j];
        while(i<j && flag>=array[i]) i++;
        array[j] = array[i];
    }
    array[i] = flag;
    quickSort(array, begin, i);
    quickSort(array, i+1, end);
}
```
### 冒泡排序
1. 时间复杂度: 平均 O(n<sup>2</sup>) 最好O(n) 最坏O(n<sup>2</sup>) 
2. 空间复杂度: O(1)
3. 稳定性: 是
4. 描述: 重复遍历数组, 依次比较相邻元素, 顺序有误交换.
5. 适用场景: 在数组较小时使用, 通常不使用
6. 代码:
```java
public void sort(int[] array){
    boolean done = false;
    for(int i=0;i<array.length - 1&&!done;i++){
        for(int k=array.length - 1; k>i;k--){
            done = true;
            if(array[k]< array[k-1]){
                int temp = array[k];
                array[k] = array[k-1];
                array[k-1] = temp;
                done = false;
            }
        }
    }
}
```
### 选择排序
1. 时间复杂度: O(n<sup>2</sup>)
2. 空间复杂度: O(1)
3. 稳定性: 否
4. 描述: 遍历数组, 选择最小元素对应的下标, 最后交换
5. 适用场景: 数据量较小
6. 代码:
```java
public void sort(int[] array){
    for(int i=0;i<array.length - 1;i++){
        int k = i;
        for(int j=0;j<array.length;j++){
            if(array[j]<array[k]){
                k = j;
            }
        }
        if(k!=i){
            int temp = array[k];
            array[k] = array[i];
            array[i] = temp;
        }
    }
}
```
### 堆排序
1. 时间复杂度: O(nlog<sub>2</sub>n)
2. 空间复杂度: O(1)
3. 稳定性: 否
4. 描述: 把数组看为一个完全二叉树, 通过交换构造最大堆或者最小堆
5. 适用场景: 数据量较大时, 空间要求严格时
6. 代码
```java
public void sort(int[] array){
    for(int i=(array.length - 2) >> 1;i>=0;i--){
        maxHeap(array, i, array.length);
    }
    int temp = 0;
    for(int i=0;i<array.length - 1;i++){
        temp = array[array.length - i - 1];
        array[array.length - i - 1] = array[0];
        array[0] = temp;
        maxHeap(array, 0, array.length - i - 1);
    }
}
public void maxHeap(int[] array, int root, int length){
    int left = (root<<1) + 1;
    int right = (root<<1) + 2;
    int min = root;
    int temp;
    
    if(left<length){
        if(array[min]<array[left]) min = left;
    }
    if(right<length){
        if(array[min]<array[right]) min = right;
    }
    if(min != root){
        temp = array[root];
        array[root] = array[min];
        array[min] = temp;
        maxHeap(array, min, length);
    }
}
```