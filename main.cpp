#include <iostream>
#include "src/FiniteStateMachine.h"
#include "src/DeterminedFiniteStateMachine.h"

int main() {
  FiniteStateMachine machine;
  std::string input_file;
  std::cin >> input_file;
  machine.EnterMachine(input_file);
  std::cout << "You've entered the following machine:\n";
  machine.PrintMachine();
  machine.GetRidOfEpsTransitions();
  std::cout << "Machine without epsilon-transitions:\n";
  machine.PrintMachine();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  std::cout << "Determined Finite State Machine:\n";
  machine2.PrintDFSM();
  machine2.MakeFull();
  std::cout << "Full Determined Finite State Machine:\n";
  machine2.PrintDFSM();
  std::cout << "Enter num of calls: ";
  int num_of_calls = 0;
  std::cin >> num_of_calls;
  for (int i = 0; i < num_of_calls; ++i) {
    std::string word;
    std::cin >> word;
    if(machine2.Readable(word)) {
      std::cout << "is in language\n";
    } else {
      std::cout << "is not in language\n";
    }
  }
  machine2.MakeAddition();
  std::cout << "Addition to Full Determined Finite State Machine:\n";
  machine2.PrintDFSM();
  return 0;
}
