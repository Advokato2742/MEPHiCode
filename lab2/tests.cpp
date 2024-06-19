#include "seq.h"
#include "secondary-func.h"
#include <cassert>

template <typename T>
int CreatingPlusGetLength(int* data, int count) {
	T seq = T(data, count);
	assert(seq.GetLength() == count);
	T newseq = T(seq);
	assert(seq.GetLength() == newseq.GetLength());
	T empty = T();
	assert(empty.GetLength() == 0);
	return 1;
}

template <typename T>
int GetFirst(T* seq, int* data, int count) {
	try {
		seq->GetFirst();
		assert(seq->GetFirst() == data[0]);
	} catch(std::out_of_range) {
		if (count) {
			assert(false);
		}
	}
	return 1;
}

template <typename T>
int GetLast(T* seq, int* data, int count) {
	try {
		seq->GetLast();
		assert(seq->GetLast() == data[count-1]);
	}
	catch(std::out_of_range) {
		if (count) {
			assert(false);
		}
	}
	return 1;
}

template <typename T>
int GetElement(T* seq, int* data, int count) {
	for (int i = 0; i < count; i++) {
		try {
			assert(seq->GetElement(i) == data[i]);
		} catch(std::out_of_range) {
			if (count) {
				assert(false);
			}
		}
	}
	
	try {
		seq->GetElement(count);
		assert(false);
	} catch(std::out_of_range) {  }
	
	try {
		seq->GetElement(-1);
		assert(false);
	} catch(std::out_of_range) {  }
	return 1;
}

template <typename T>
int OperatorComparison(T* seq, int* data, int count) {
	T newseq = T(data, count);
	bool exp = true;
	for (int i = 0; i < count; i++) {
		if (seq->GetElement(i) != newseq.GetElement(i)) {
			exp = false;
			break;
		}
	}
	bool res = (*seq == newseq);
	assert(res == exp);
	
	int arr[4] = {1, 2, 3, 4};
	T first = T(arr, 4);
	res = (first == newseq);
	assert(res != exp);
	
	arr[1] = 0;
	T second = T(arr, 4);
	res = (second == first);
	assert(res != exp);
	return 1;
}

template <typename T>
int Append(T* seq, int* data, int count) {
	T seq1 = T(data, 5);
	seq1.Append(6);
	assert(seq1.GetLength() == 6 && seq1.GetLast() == 6);
	
	T seq2 = T();
	seq2.Append(4);
	assert(seq2.GetLength() == 1 && seq2.GetLast() == 4);
	return 1;
}

template <typename T>
int Prepend(T* seq, int* data, int count) {
	T seq1 = T(data, 5);
	seq1.Prepend(6);
	assert(seq1.GetLength() == 6 && seq1.GetFirst() == 6);
	
	T seq2 = T();
	seq2.Prepend(4);
	assert(seq2.GetLength() == 1 && seq2.GetFirst() == 4);
	return 1;
}

template <typename T>
int InsertAt(T* seq) {
	int arr1[4] = {1, 2, 4, 5};
	T seq1 = T(arr1, 4);
	try {
		seq1.InsertAt(3, 2);
		assert(seq1 == *seq);
	} catch(std::out_of_range) {
		assert(false);
	}
	
	int arr2[4] = {2, 3, 4, 5};
	T seq2 = T(arr2, 4);
	try {
		seq2.InsertAt(1, 0);
		assert(seq2 == *seq);
	} catch(std::out_of_range) {
		assert(false);
	}
	
	int arr3[4] = {1, 2, 3, 4};
	T seq3 = T(arr3, 4);
	try {
		seq3.InsertAt(5, 4);
		assert(seq3 == *seq);
	} catch(std::out_of_range) {
		assert(false);
	}
	
	int arr4[1] = {1};
	T seq4 = T(arr4, 1);
	T empty = T();
	try {
		empty.InsertAt(1, 0);
		assert(empty == seq4);
	} catch(std::out_of_range) {
		assert(false);
	}
	
	try {
		seq->InsertAt(4, seq->GetLength()+1);
		assert(false);
	} catch(std::out_of_range) {  }
	
	try {
		seq->InsertAt(4, -1);
		assert(false);
	} catch(std::out_of_range) {  }
	return 1;
}

template <typename T>
int Concat(T* seq) {
	int arr[10] = {2, 2, 3, 4, 5, 1, 2, 3, 4, 5};
	int test[5] = {2, 2, 3, 4, 5};
	T exp = T(arr, 10);
	T arg = T(test, 5);
	T* res = (T*)(arg + seq);
	assert(*res == exp);
	delete res;
	return 1;
}

template <typename T>
int GetSubSequence(T* seq, int* data, int count, int start, int end) {
	T exp = T(data, count);
	T* subseq;
	try {
		subseq = seq->GetSubsequence(start, end);
		assert(exp == *subseq);
	} catch(std::out_of_range) {
		assert(false);
	} catch(std::invalid_argument) {
		assert(false);
	}
	delete subseq;
	
	try {
		subseq = seq->GetSubsequence(-1, end);
		assert(false);
	} catch(std::invalid_argument) {
		assert(false);
	} catch(std::out_of_range) {  }
	
	try {
		subseq = seq->GetSubsequence(start, seq->GetLength()+1);
		assert(false);
	} catch(std::invalid_argument) {
		assert(false);
	} catch(std::out_of_range) {  }
	
	try {
		subseq = seq->GetSubsequence(end, start);
		assert(exp == *subseq);
	} catch(std::out_of_range) {
		assert(false);
	} catch(std::invalid_argument) {  }

	return 1;
}

template <typename T>
int ImmutAppend(T* res, int* data, int count) {
	int arr[4] = {1, 2, 3, 4};
	T seq = T(arr, 4);
	T* newseq = seq.ImmutableAppend(5);
	T oldseq = T(arr, 4);
	assert(*res == *newseq && seq == oldseq);
	delete newseq;
	return 1;
}

template <typename T>
int ImmutPrepend(T* res, int* data, int count) {
	int arr[4] = {2, 3, 4, 5};
	T seq = T(arr, 4);
	T* newseq = seq.ImmutablePrepend(1);
	T oldseq = T(arr, 4);
	assert(*res == *newseq && seq == oldseq);
	delete newseq;
	return 1;
}

template <typename T>
int ImmutInsertAt(T* res, int* data, int count) {	
	int arr1[4] = {1, 2, 4, 5};
	T seq1 = T(arr1, 4);
	T oldseq = T(arr1, 4);
	T* newseq;
	try {
		newseq = seq1.ImmutableInsertAt(3, 2);
		assert(*res == *newseq && seq1 == oldseq);
	} catch(std::out_of_range) {
		assert(false);
	}
	delete newseq;
	
	int arr2[4] = {2, 3, 4, 5};
	T seq2 = T(arr2, 4);
	T oldseq2 = T(arr2, 4);
	try {
		newseq = seq2.ImmutableInsertAt(1, 0);
		assert(*res == *newseq && seq2 == oldseq2);
	} catch(std::out_of_range) {
		assert(false);
	}
	delete newseq;

	int arr3[4] = {1, 2, 3, 4};
	T seq3 = T(arr3, 4);
	T oldseq3 = T(arr3, 4);
	try {
		newseq = seq3.ImmutableInsertAt(5, 4);
		assert(*res == *newseq && seq3 == oldseq3);
	} catch(std::out_of_range) {
		assert(false);
	}
	delete newseq;
	
	int arr4[1] = {1};
	T seq4 = T(arr4, 1);
	T empty = T();
	T oldseq4 = T();
	try {
		newseq = empty.ImmutableInsertAt(1, 0);
		assert(seq4 == *newseq && empty == oldseq4);
	} catch(std::out_of_range) {
		assert(false);
	}
	delete newseq;
	
	try {
		T* badseq1 = seq3.ImmutableInsertAt(1, -1);
		assert(false);
	} catch(std::out_of_range) {  }

	try {
		T* badseq2 = seq3.ImmutableInsertAt(1, seq3.GetLength()+1);
		assert(false);
	} catch(std::out_of_range) {  }
	
	return 1;
}

void ArrayTest(){
	int arr[5] = {1, 2, 3, 4, 5};
	int len = 5;
	int s = 0;
	
	s += CreatingPlusGetLength<ArraySequence<int>>(arr, len);
	ArraySequence<int> seq = ArraySequence<int>(arr, len);
	s += GetFirst(&seq, arr, len);
	s += GetLast(&seq, arr, len);
	s += GetElement(&seq, arr, len);
	s += OperatorComparison(&seq, arr, len);
	s += Append(&seq, arr, len);
	s += Prepend(&seq, arr, len);
	s += InsertAt(&seq); //9
	s += Concat(&seq);
	s += GetSubSequence(&seq, arr, len, 0, len-1);
	s += ImmutAppend(&seq, arr, len);
	s += ImmutPrepend(&seq, arr, len);
	s += ImmutInsertAt(&seq, arr, len);//13
	
	int arr2[0];
	ArraySequence<int> seq2 = ArraySequence<int>();
	s += GetFirst(&seq2, arr2, 0);
	std::cout << s << std::endl;
}
void ListTest(){
	int arr[5] = {1, 2, 3, 4, 5};
	int len = 5;
	int s = 0;
	
	s += CreatingPlusGetLength<ListSequence<int>>(arr, len);
	ListSequence<int> seq = ListSequence<int>(arr, len);
	s += GetFirst(&seq, arr, len);
	s += GetLast(&seq, arr, len);
	s += GetElement(&seq, arr, len);
	s += OperatorComparison(&seq, arr, len);
	s += Append(&seq, arr, len);
	s += Prepend(&seq, arr, len);
	s += InsertAt(&seq); //9
	s += Concat(&seq);
	s += GetSubSequence(&seq, arr, len, 0, len-1);
	s += ImmutAppend(&seq, arr, len);
	s += ImmutPrepend(&seq, arr, len);
	s += ImmutInsertAt(&seq, arr, len);//13
	
	int arr2[0];
	ListSequence<int> seq2 = ListSequence<int>();
	s += GetFirst(&seq2, arr2, 0);
	std::cout << s << std::endl;
}

int main() {
	ArrayTest();
	ListTest();
	return 0;
}
