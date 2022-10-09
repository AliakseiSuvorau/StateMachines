#include <iostream>
#include <vector>
#include <string>

class FiniteStateMachine {
  struct arrow;

  struct state {
    bool is_beginning = false;
    bool is_accept = false;
    std::vector<arrow> from_cur;
    std::vector<arrow> to_cur;
  };
  struct arrow {
    char letter = '-';
    int to_state = -1;
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
      if (alphabet.find(nullptr, alphabet.size(), letter) == alphabet.size()) {
        alphabet += std::to_string(letter);
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
    std::cout << "Enter ----- OK\n";
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
    std::cout << "Epsilon Loops Deleting ----- OK\n";
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
    std::cout << "Epsilon Transitions Making ----- OK\n";
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
    std::cout << "Epsilon Transitions Deleting ----- OK\n";
  }

};

int main() {
  FiniteStateMachine machine;
  machine.EnterMachine();
  machine.PrintMachine();
  machine.GetRidOfEpsTransitions();
  machine.PrintMachine();
  return 0;
}
