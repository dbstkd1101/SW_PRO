#pragma once
#ifndef NULL
#define NULL 0
#endif
#include <string.h>

#define NEXT_NODE_CNT 26

struct Trie {
	Trie* next[NEXT_NODE_CNT];
	Trie() {
		memset(this->next, 0, sizeof(this->next));
	}
	void add(char *str) {
		if (*str != NULL) {
			if (next[*str - 'a'] == NULL) next[*str - 'a'] = new Trie();
			next[*str - 'a']->add(str + 1);
		}
	}

	Trie* get(char* str) {
		if (*str != NULL) {
			if (next[*str - 'a']) return next[*str - 'a']->get(str + 1); //recursive
			return 0; //faill to find str
		}
		else {
			return this; //find end node
		}
	}

	void clear() {
		for (int i = 0; i < NEXT_NODE_CNT; i++) {
			if (next[i]) {
				next[i]->clear();
				delete next[i];
			}
		}
	}
};