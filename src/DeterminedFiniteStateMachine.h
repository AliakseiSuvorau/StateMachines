#ifndef PRAC2_SRC_DETERMINEDFINITESTATEMACHINE_H_
#define PRAC2_SRC_DETERMINEDFINITESTATEMACHINE_H_

#endif //PRAC2_SRC_DETERMINEDFINITESTATEMACHINE_H_

#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include "FiniteStateMachine.h"

class DeterminedFiniteStateMachine {
  struct state {
    std::set<int> set_of_states;
    bool is_beginning = false;
    bool is_accept = false;
    int index_of_state = -1;
    std::vector<arrow> from_cur;
    std::vector<arrow> to_cur;
  };

  std::vector<state> states_fsm;
  std::vector<state> states_dfsm;
  int index_of_beginning_state = -1;

 public:
  DeterminedFiniteStateMachine() = default;

  ~DeterminedFiniteStateMachine() = default;

 private:
  std::string alphabet;

  void AddStateToFSM(std::set<int>& set, bool is_beginning, bool is_accept) {
    state state;
    state.is_accept = is_accept;
    state.is_beginning = is_beginning;
    state.set_of_states = set;
    states_fsm.push_back(state);
  }

  int AddStateToDFSM(std::set<int>& set, bool is_beginning, bool is_accept) {
    for (int i = 0; i < states_dfsm.size(); ++i) {
      if (set == states_dfsm[i].set_of_states) {
        return i;
      }
    }
    state state;
    state.is_accept = is_accept;
    state.is_beginning = is_beginning;
    if (state.is_beginning) {
      index_of_beginning_state = states_dfsm.size();
    }
    state.set_of_states = set;
    state.index_of_state = states_dfsm.size();
    states_dfsm.push_back(state);
    return states_dfsm.size() - 1;
  }

  void AddArrowFSM(int from, int to, char letter) {
    states_fsm[from].from_cur.push_back({letter, to});
    states_fsm[to].to_cur.push_back({letter, from});
  }

  bool CheckForExistence(int from, int to, char letter) {
    for (int i = 0; i < states_dfsm[from].from_cur.size(); ++i) {
      if (states_dfsm[from].from_cur[i].to_state == to && states_dfsm[from].from_cur[i].letter == letter) {
        return true;
      }
    }
    return false;
  }

  void AddArrowDFSM(int from, int to, char letter) {
    if (!CheckForExistence(from, to, letter)) {
      states_dfsm[from].from_cur.push_back({letter, to});
      states_dfsm[to].to_cur.push_back({letter, from});
    }
  }

 private:
  void PrintState(int i) {
    if (states_dfsm[i].is_beginning) {
      if (states_dfsm[i].is_accept) {
        std::cout << "-->\t" << "[";
        for (const auto &item : states_dfsm[i].set_of_states) {
          if (item != *(states_dfsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "]" << "\t\t";
      } else {
        std::cout << "-->\t" << " ";
        for (const auto &item : states_dfsm[i].set_of_states) {
          if (item != *(states_dfsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "\t\t";
      }
    } else {
      if (states_dfsm[i].is_accept) {
        std::cout << "\t[";
        if (states_dfsm[i].set_of_states.empty()) {
          std::cout << "T";
        }
        for (const auto &item : states_dfsm[i].set_of_states) {
          if (item != *(states_dfsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "]\t\t";
      } else {
        std::cout <<"\t" << " ";
        if (states_dfsm[i].set_of_states.empty()) {
          std::cout << "T";
        }
        for (const auto &item : states_dfsm[i].set_of_states) {
          if (item != *(states_dfsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "\t\t";
      }
    }
  }

  void PrintStateWithoutBeginning(int i) {
    if (states_dfsm[i].is_accept) {
      std::cout << "\t[";
      if (states_dfsm[i].set_of_states.empty()) {
        std::cout << "T";
      }
      for (const auto &item : states_dfsm[i].set_of_states) {
        if (item != *(states_dfsm[i].set_of_states.begin())) {
          std::cout << ", ";
        }
        std::cout << item + 1;
      }
      std::cout << "]\t";
    } else {
      std::cout <<"\t" << " ";
      if (states_dfsm[i].set_of_states.empty()) {
        std::cout << "T";
      }
      for (const auto &item : states_dfsm[i].set_of_states) {
        if (item != *(states_dfsm[i].set_of_states.begin())) {
          std::cout << ", ";
        }
        std::cout << item + 1;
      }
      std::cout << "\t\t";
    }
  }

 public:
  void EnterNSM(FiniteStateMachine& FSM) {
    alphabet = FSM.alphabet;
    for (int i = 0; i < FSM.num_of_states; ++i) {
      std::set<int> set = {i};
      AddStateToFSM(set, FSM.IsBegining(i), FSM.IsAccept(i));
    }
    for (int i = 0; i < FSM.num_of_states; ++i) {
      for (int j = 0; j < FSM.GetNumOfArrows(i); ++j) {
        arrow arrow = FSM.GetArrow(i, j);
        AddArrowFSM(i, arrow.to_state, arrow.letter);
      }
    }
  }

  void PrintDFSM() {
    for (int i = 0; i < states_dfsm.size(); ++i) {
      for (int j = 0; j < states_dfsm[i].from_cur.size(); ++j) {
        PrintState(i);
        if (states_dfsm[i].from_cur[j].letter == '-') {
          std::cout << "eps\t";
        } else {
          std::cout << states_dfsm[i].from_cur[j].letter << "\t";
        }
        PrintStateWithoutBeginning(states_dfsm[i].from_cur[j].to_state);
        std::cout << "\n";
      }
    }
  }

  int FindBeginningIndex () {
    for (int i = 0; i < states_fsm.size(); ++i) {
      if (states_fsm[i].is_beginning) {
        return i;
      }
    }
    return -1;
  }

  void MakeDFSM() {
    int beginningIndex = FindBeginningIndex();
    AddStateToDFSM(states_fsm[beginningIndex].set_of_states, states_fsm[beginningIndex].is_beginning, states_fsm[beginningIndex].is_accept);
    std::queue<state> queue;
    queue.push(states_dfsm[0]);
    while (!queue.empty()) {
      state cur_state = queue.front();
      queue.pop();
      for (const auto &letter : alphabet) { // по всем буквам из алфавита
        state new_state;
        for (const auto &state_from_set : cur_state.set_of_states) { // по всем вершинам из множества
          for (int j = 0; j < states_fsm[state_from_set].from_cur.size(); ++j) { // по всем ребрам из каждой вершины
            if (states_fsm[state_from_set].from_cur[j].letter == letter) {
              new_state.set_of_states.insert(states_fsm[state_from_set].from_cur[j].to_state);
              if (states_fsm[states_fsm[state_from_set].from_cur[j].to_state].is_accept) {
                new_state.is_accept = true;
              }
            }
          }
        }
        if (new_state.set_of_states == cur_state.set_of_states) { // проверка на петли
          AddArrowDFSM(cur_state.index_of_state, cur_state.index_of_state, letter);
        } else {
          if (!new_state.set_of_states.empty()) {
            int index_of_new_state = AddStateToDFSM(new_state.set_of_states, new_state.is_beginning, new_state.is_accept);
            AddArrowDFSM(cur_state.index_of_state, index_of_new_state, letter);
            if (index_of_new_state == states_dfsm.size() - 1) {
              queue.push(states_dfsm[index_of_new_state]);
            }
          }
        }
      }
    }
  }

  void MakeFull() {
    int trash_state_index = states_dfsm.size();
    states_dfsm.push_back({{}, false, false, trash_state_index, {}, {}});
    for (int i = 0; i < states_dfsm.size(); ++i) {
      for (const auto &letter : alphabet) {
        int flag = 0;
        for (int j = 0; j < states_dfsm[i].from_cur.size(); ++j) {
          if (CheckForExistence(i, states_dfsm[i].from_cur[j].to_state, letter)) {
            ++flag;
          }
        }
        if(!flag) {
          if (letter != '-') {
            AddArrowDFSM(i, trash_state_index, letter);
          }
        }
      }
    }
    for (const auto &letter : alphabet) {
      if (letter != '-') {
        AddArrowDFSM(trash_state_index, trash_state_index, letter);
      }
    }
  }

  void MakeAddition() {
    for (int i = 0; i < states_dfsm.size(); ++i) {
      if (states_dfsm[i].is_accept) {
        states_dfsm[i].is_accept = false;
      } else {
        states_dfsm[i].is_accept = true;
      }
    }
  }

  bool Readable(const std::string& word) {
    int index = index_of_beginning_state;
    for (int i = 0; i < word.size(); ++i) {
      for (int j = 0; j < states_dfsm[index].from_cur.size(); ++j) {
        if (states_dfsm[index].from_cur[j].letter == word[i]) {
          index = states_dfsm[index].from_cur[j].to_state;
          break;
        }
      }
    }
    return states_dfsm[index].is_accept;
  }

  int size() {
    return states_dfsm.size();
  }
};