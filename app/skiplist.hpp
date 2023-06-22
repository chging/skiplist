
#ifndef ___SKIP_LIST_HPP
#define ___SKIP_LIST_HPP

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace SKLT {

template<typename Key, typename Value>
class SkipList
{

private:
	struct Node {
		Key key;
		Value value;
		std::vector<Node*> forward;

		Node(const Key&k, const Value&v) {
			key = k;
			value = v;
		}

		Node() {
		}
	};

private:
	// private variables go here.
	Node* header_ = nullptr;
	//level of the list, start from 0
	int level_ = 0;
	//key size
	int size_ = 0;
public:

	SkipList();
	~SkipList();

	SkipList(const SkipList&) = delete;
	SkipList& operator=(const SkipList&) = delete;

	/**
	 * @brief      get size of key in the skip list
	 *
	 * @return     { description_of_the_return_value }
	 */
	size_t size() const;
	/**
	 * @brief      Determines if empty.
	 *
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty() const;
	/**
	 * @brief     get layer of the list
	 *
	 * @return layer of the list
	 */
	unsigned numLayers() const;
	/**
	 * @brief      get height of the given key
	 *
	 * @param[in]  k     The key
	 *
	 * @return     if the key exist, return height of the key, -1 otherwise
	 */
	int height(const Key & k) const;
	/**
	 * @brief      Searches for the key.
	 *
	 * @param[in]  k     The key
	 * @param      v     value associated with the given key
	 *
	 * @return    if the key is exist, return True and v is value associated with the given key, False otherwise
	 */
	bool find(const Key & k, Value& v) const;
	/**
	 * @brief      Searches for the key.
	 *
	 * @param[in]  k     The key
	 *
	 * @return     True if the key exist, False otherwise
	 */
	bool find(const Key & k) const;
	/**
	 * @brief    insert a key
	 *
	 * @param[in]  k     The key
	 * @param[in]  v     The value
	 *
	 * @return     if the key exists, not insert and return false, True otherwise
	 */
	bool insert(const Key & k, const Value & v);
	/**
	 * @brief      Return a vector containing all inserted keys in increasing order
	 *
	 * @return     all keys
	 */
	std::vector<Key> allKeysInOrder() const;
	/**
	 * @brief      Determines whether the specified k is smallest key.
	 *
	 * @param[in]  k  The key
	 *
	 * @return     True if the specified k is smallest key, False otherwise.
	 */
	bool isSmallestKey(const Key & k) const;
	/**
	 * @brief      Determines whether the specified k is largest key.
	 *
	 * @param[in]  k  The key
	 *
	 * @return     True if the specified k is largest key, False otherwise.
	 */
	bool isLargestKey(const Key & k) const;
	/**
	 * @brief      remove key
	 *
	 * @param[in]  key    The key
	 * @param      value  The value
	 *
	 * @return     if key is exist, return True, False otherwise
	 */
	bool remove(const Key& key);
	/**
	 * @brief print this list, it is just for test
	 */
	void displayList() const;

protected:
	/**
	 * @brief      generator random level.
	 * for a skip list with 16 or fewer elements the maximum number of layers is 13;for a skip list with more than 16 elements the maximum number of layers is 3 *
	 * ceil(log 2 (n)) + 1
	 * @return     The random level.
	 */
	int getRandomLevel() const;

};

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList() {
	header_ = new Node();
	header_->forward.resize(1);
	header_->forward[0] = nullptr;
}

template<typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
	Node *node = header_;
	Node* tmp = nullptr;
	while (node) {
		tmp = node->forward[0];
		delete node;
		node = tmp;
	}
}

template<typename Key, typename Value>
size_t SkipList<Key, Value>::size() const  {
	return size_;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isEmpty() const  {
	return size_ == 0;
}

template<typename Key, typename Value>
unsigned SkipList<Key, Value>::numLayers() const {
	return level_ + 1;
}

template<typename Key, typename Value>
int SkipList<Key, Value>::height(const Key & k) const {

	Node *node = header_;
	int l = 0;
	for (l = level_; l >= 0; l--) {
		while (node && node->forward[l] && node->forward[l]->key < k) {
			node = node->forward[l];
		}

		if (node->forward[l] && node->forward[l]->key == k) {
			return l;
		}
	}

	return -1;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::find(const Key& k, Value& value) const {

	Node *node = header_;
	for (int l = level_; l >= 0; l--) {
		while (node && node->forward[l] && node->forward[l]->key < k) {
			node = node->forward[l];
		}
	}

	if (node && node->forward[0] && node->forward[0]->key == k) {
		value = node->forward[0]->value;
		return true;
	}

	return false;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::find(const Key& k) const {
	Value v;
	return find(k, v);
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::insert(const Key & key, const Value & value) {

	auto update = std::make_shared< std::vector<Node*> >(level_ + 1, nullptr);

	Node *node = header_;

	for (int i = level_; i >= 0; --i) {
		while ( node && node->forward[i] && node->forward[i]->key < key) {
			node = node->forward[i];
		}
		update->at(i) = node;
	}

	node = node->forward[0];
	//if key exist, return false
	if (node && node->key == key) {
		return false;
	}

	int nodeLevel = getRandomLevel();

	if (nodeLevel > level_) {
		++level_;
		update->push_back(header_);
		header_->forward.resize(level_ + 1);
	}

	Node *newNode = new Node(key, value);
	newNode->forward.resize(level_ + 1);

	for (int i = level_; i >= 0; --i) {
		node = update->at(i);
		newNode->forward[i] = node->forward[i];
		node->forward[i] = newNode;
	}

	++size_;

	return true;
}

template<typename Key, typename Value>
std::vector<Key> SkipList<Key, Value>::allKeysInOrder() const {
	std::vector<Key> data;
	Node* node = header_->forward[0];
	while (node) {
		data.push_back(node->key);
		node = node->forward[0];
	}

	return data;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isSmallestKey(const Key & k) const {
	if (header_->forward[0] && header_->forward[0]->key == k) {
		return true;
	}

	return false;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isLargestKey(const Key & k) const {

	Node *node = header_;
	int l = 0;
	for (l = level_; l >= 0; l--) {
		while (node && node->forward[l] && node->forward[l]->key < k) {
			node = node->forward[l];
		}
	}

	Node *forward = node->forward[0];
	if (forward && forward->key == k && !forward->forward[0]) {
		return true;
	}

	return false;
}

template<typename Key, typename Value>
void SkipList<Key, Value>::displayList() const {
	for (int i = level_; i >= 0; i--) {
		Node *node = header_->forward[i];
		while (node != NULL) {
			node = node->forward[i];
		}
	}
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::remove(const Key& key) {

	auto update = std::make_shared< std::vector<Node*> >(level_ + 1, nullptr);

	Node *node = header_;
	for (int i = level_; i >= 0; --i) {
		while ( node && node->forward[i] && node->forward[i]->key < key) {
			node = node->forward[i];
		}
		update->at(i) = node;
	}

	node = node->forward[0];

	if (!node || node->key != key) {
		return false;
	}

	for (int i = 0; i <= level_; ++i) {
		if (update->at(i)->forward[i] != node) {
			break;
		}
		update->at(i)->forward[i] = node->forward[i];
	}

	delete node;

	while (level_ > 0 && header_->forward[level_] == nullptr) {
		--level_;
	}

	--size_;

	return true;
}

template<typename Key, typename Value>
int SkipList<Key, Value>::getRandomLevel() const {

	if (size_ <= 0) {
		return 0;
	}

	int max_level = 13;
	if (size_ <= 16) {
		max_level = 13;
	} else {
		max_level = 3 * ceil(log2(size_)) + 1;
	}

	int level = std::rand() % max_level;

	return level;
}


}

#endif

