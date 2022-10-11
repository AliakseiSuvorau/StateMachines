#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>

struct arrow {
  char letter = '-';
  int to_state = -1;
};

class FiniteStateMachine {

  struct state {
    bool is_beginning = false;
    bool is_accept = false;
    std::vector<arrow> from_cur;
    std::vector<arrow> to_cur;
  };

  std::vector<state> states;

 public:

  int num_of_states = 0;
  std::string alphabet;

 public:
  FiniteStateMachine() = default;
  ~FiniteStateMachine() = default;

  void EnterMachine() {
    std::cout << "Enter the number of states: ";
    std::cin >> num_of_states;
    states.resize(num_of_states);
    std::cout << "Enter number of transitions: ";
    int num_of_transitions;
    std::cin >> num_of_transitions;
    std::cout << "Enter transitions in order: (from_state) (letter) (to_state)\n"; //- for epsilon
    for (int i = 0; i < num_of_transitions; ++i) {
      int from, to;
      char letter;
      std::cin >> from >> letter >> to;
      states[from - 1].from_cur.push_back({letter, to - 1});
      states[to - 1].to_cur.push_back({letter, from - 1});
      if (alphabet.find(letter) == std::string::npos) {
        alphabet += letter;
      }
    }
    std::cout << "Enter the index of the beginning state: ";
    int index_of_beginning;
    std::cin >> index_of_beginning;
    states[index_of_beginning - 1].is_beginning = true;
    std::cout << "Enter the number of accepting states: ";
    int num_of_accept;
    std::cin >> num_of_accept;
    std::cout << "Enter all the accepting states:\n";
    for (int i = 0; i < num_of_accept; ++i) {
      int index_of_accept;
      std::cin >> index_of_accept;
      states[index_of_accept - 1].is_accept = true;
    }
    //std::cout << "Enter ----- OK\n";/////////////////////////////////////////
  }

  void PrintMachine() {
    for (int i = 0; i < states.size(); ++i) {
      for (int j = 0; j < states[i].from_cur.size(); ++j) {
        if (states[i].is_beginning) {
          if (states[i].is_accept) {
            std::cout << "-->\t" << "[" << i + 1 << "]" << "\t";
          } else {
            std::cout << "-->\t" << " " << i + 1 << "\t";
          }
        } else {
          if (states[i].is_accept) {
            std::cout << "\t[" << i + 1 << "]\t";
          } else {
            std::cout <<"\t" << " " << i + 1 << "\t";
          }
        }
        if (states[i].from_cur[j].letter == '-') {
          std::cout << "eps\t";
        } else {
          std::cout << states[i].from_cur[j].letter << "\t";
        }
        if (states[states[i].from_cur[j].to_state].is_accept) {
          std::cout << "[" << states[i].from_cur[j].to_state + 1 << "]\t";
        } else {
          std::cout << " " << states[i].from_cur[j].to_state + 1 << "\t";
        }
        std::cout << "\n";
      }
    }
  }
 private:

  void ArrowDelete(int i, int j) {
    int to_state = states[i].from_cur[j].to_state;
    for (int k = 0; k < states[to_state].to_cur.size(); ++k) {
      if (states[to_state].to_cur[k].to_state == i) {
        for (int t = k + 1; t < states[to_state].to_cur.size(); ++t) {
          states[to_state].to_cur[t - 1] = states[to_state].to_cur[t];
        }
        states[to_state].to_cur.pop_back();
        break;
      }
    }
    for (int k = j + 1; k < states[i].from_cur.size(); ++k) {
      states[i].from_cur[k - 1] = states[i].from_cur[k];
    }
    states[i].from_cur.pop_back();
  }

 public:
  void GetRidOfEpsLoops() {
    for (int i = 0; i < num_of_states; ++i) {
      for (int j = 0; j < states[i].from_cur.size(); ++j) {
        if (states[i].from_cur[j].to_state == i && states[i].from_cur[j].letter == '-') {
          ArrowDelete(i,j);
          j--;
        }
      }
    }
    //std::cout << "Epsilon Loops Deleting ----- OK\n";////////////////////////////////////////////////
  }

 private:
  bool CheckForExistence(int from, int to, char letter) {
    for (int i = 0; i < states[from].from_cur.size(); ++i) {
      if (states[from].from_cur[i].to_state == to && states[from].from_cur[i].letter == letter) {
        return true;
      }
    }
    return false;
  }

  void MakeArrow(int from, int to, char letter) {
    if (!CheckForExistence(from, to, letter)) {
      states[from].from_cur.push_back({letter, to});
      states[to].to_cur.push_back({letter, from});
    }
  }

  void MakeEpsilonTransition() {
    for (int i = 0; i < states.size(); ++i) {
      for (int j = 0; j < states[i].from_cur.size(); ++j) { //по всем ребрам из i-й вершины
        if (states[i].from_cur[j].letter == '-') { //если это эплилон-ребро
          int index_of_new_state = states[i].from_cur[j].to_state;
          for (int k = 0; k < states[index_of_new_state].from_cur.size(); ++k) { //по всем ребрам из вершины, соедененной с i-й ребром j
            if (states[index_of_new_state].from_cur[k].letter == '-') {
              MakeArrow(i, states[index_of_new_state].from_cur[k].to_state, '-'); // добавляем транзитивный эпсилон-переход
            }
          }
        }
      }
    }
    //std::cout << "Epsilon Transitions Making ----- OK\n";/////////////////////////////////////////////////
  }

  void DeleteAllEpsilonTransitions() {
    for (int i = 0; i < states.size(); ++i) {
      for (int j = 0; j < states[i].from_cur.size(); ++j) {
        if (states[i].from_cur[j].letter == '-') {
          ArrowDelete(i, j);
          j--;
        }
      }
    }
  }

 public:
  void GetRidOfEpsTransitions() {
    GetRidOfEpsLoops();
    MakeEpsilonTransition();
    for (int i = 0; i < states.size(); ++i) {
      for (int j = 0; j < states[i].from_cur.size(); ++j) {
        if (states[i].from_cur[j].letter == '-') {
          if (states[states[i].from_cur[j].to_state].is_accept) {
            states[i].is_accept = true;
          }
          for (int k = 0; k < states[states[i].from_cur[j].to_state].from_cur.size(); ++k) {
            char letter = states[states[i].from_cur[j].to_state].from_cur[k].letter;
            MakeArrow(i, states[states[i].from_cur[j].to_state].from_cur[k].to_state, letter);
          }
          for (int k = 0; k < states[i].to_cur.size(); ++k) {
            MakeArrow(states[i].to_cur[k].to_state, states[i].from_cur[j].to_state, states[i].to_cur[k].letter);
          }
        }
      }
    }
    DeleteAllEpsilonTransitions();
    //std::cout << "Epsilon Transitions Deleting ----- OK\n";///////////////////////////////////////////////
  }

  bool IsBegining(int i) {
    return states[i].is_beginning;
  }

  bool IsAccept(int i) {
    return states[i].is_accept;
  }

  int GetNumOfArrows(int state) {
    return states[state].from_cur.size();
  }

  arrow GetArrow(int state, int j) {
    return states[state].from_cur[j];
  }
};

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
    //std::cout << "adding arrow from " << from + 1 << " letter " << letter << " to " << to + 1 << "\n";////////////////////////////////////////
    if (!CheckForExistence(from, to, letter)) {
      states_dfsm[from].from_cur.push_back({letter, to});
      states_dfsm[to].to_cur.push_back({letter, from});
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
//////////////////////////////////////////////////////////////////////
  void PrintState1(int i) {
    if (states_fsm[i].is_beginning) {
      if (states_fsm[i].is_accept) {
        std::cout << "-->\t" << "[";
        for (const auto &item : states_fsm[i].set_of_states) {
          if (item != *(states_fsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "]" << "\t";
      } else {
        std::cout << "-->\t" << " ";
        for (const auto &item : states_fsm[i].set_of_states) {
          if (item != *(states_fsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "\t";
      }
    } else {
      if (states_fsm[i].is_accept) {
        std::cout << "\t[";
        for (const auto &item : states_fsm[i].set_of_states) {
          if (item != *(states_fsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "]\t";
      } else {
        std::cout <<"\t" << " ";
        for (const auto &item : states_fsm[i].set_of_states) {
          if (item != *(states_fsm[i].set_of_states.begin())) {
            std::cout << ", ";
          }
          std::cout << item + 1;
        }
        std::cout << "\t";
      }
    }
  }

  void PrintStateWithoutBeginning1(int i) {
    if (states_fsm[i].is_accept) {
      std::cout << "\t[";
      for (const auto &item : states_fsm[i].set_of_states) {
        if (item != *(states_fsm[i].set_of_states.begin())) {
          std::cout << ", ";
        }
        std::cout << item + 1;
      }
      std::cout << "]\t";
    } else {
      std::cout <<"\t" << " ";
      for (const auto &item : states_fsm[i].set_of_states) {
        if (item != *(states_fsm[i].set_of_states.begin())) {
          std::cout << ", ";
        }
        std::cout << item + 1;
      }
      std::cout << "\t";
    }
  }
 public:
  void PrintFSM() {
    for (int i = 0; i < states_fsm.size(); ++i) {
      for (int j = 0; j < states_fsm[i].from_cur.size(); ++j) {
        PrintState1(i);
        if (states_fsm[i].from_cur[j].letter == '-') {
          std::cout << "eps\t";
        } else {
          std::cout << states_fsm[i].from_cur[j].letter << "\t";
        }
        PrintStateWithoutBeginning1(states_fsm[i].from_cur[j].to_state);
        std::cout << "\n";
      }
    }
  }
////////////////////////////////////////////////////
 public:
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
    //std::cout << "beginning index: " << beginningIndex + 1 << "\n";///////////////////////////////////
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
              //std::cout << "found transition from " << state_from_set + 1 << " with letter " << states_fsm[state_from_set].from_cur[j].letter << "\n"; ////////////////////////////////////
              new_state.set_of_states.insert(states_fsm[state_from_set].from_cur[j].to_state);
              if (states_fsm[states_fsm[state_from_set].from_cur[j].to_state].is_accept) {
                new_state.is_accept = true;
              }
            }
          }
        }
        if (new_state.set_of_states == cur_state.set_of_states) { // проверка на петли
          //std::cout << "hook\n";////////////////////////////////////////////////////////////////////////////////////////////////
          AddArrowDFSM(cur_state.index_of_state, cur_state.index_of_state, letter);
        } else {
          if (!new_state.set_of_states.empty()) {
            int index_of_new_state = AddStateToDFSM(new_state.set_of_states, new_state.is_beginning, new_state.is_accept);
            //std::cout << "normal\n";/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
};

int main() {
  FiniteStateMachine machine;
  machine.EnterMachine();
  std::cout << "You've entered the following machine:\n";
  machine.PrintMachine();
  std::cout << "\n\n";
  machine.GetRidOfEpsTransitions();
  std::cout << "Machine without epsilon-transitions:\n";
  machine.PrintMachine();
  std::cout << "\n\n";
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  std::cout << "Determined Finite State Machine:\n";
  machine2.PrintDFSM();
  std::cout << "\n\n";
  machine2.MakeFull();
  std::cout << "Full Determined Finite State Machine:\n";
  machine2.PrintDFSM();
  machine2.MakeAddition();
  std::cout << "Addition to Full Determined Finite State Machine:\n";
  machine2.PrintDFSM();
  return 0;
}
