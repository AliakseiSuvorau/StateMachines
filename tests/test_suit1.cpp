#include <gtest/gtest.h>
#include "../src/FiniteStateMachine.h"
#include "../src/DeterminedFiniteStateMachine.h"

TEST(epsilon_transitions, test_1) {
  std::string input_file = "../tests/test_input/eps_tests/test1.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.Readable("a"), true);
  ASSERT_EQ(machine2.Readable("aaa"), false);
  ASSERT_EQ(machine2.Readable("ab"), false);
}

TEST(epsilon_transitions, test_2) {
  std::string input_file = "../tests/test_input/eps_tests/test2.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.Readable("a"), true);
  ASSERT_EQ(machine2.Readable("aaa"), false);
  ASSERT_EQ(machine2.Readable("ab"), false);
}

TEST(epsilon_transitions, test_3) {
  std::string input_file = "../tests/test_input/eps_tests/test3.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.Readable("ab"), true);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("bb"), false);
}

TEST(epsilon_transitions, test_4) {
  std::string input_file = "../tests/test_input/eps_tests/test4.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.Readable("ab"), true);
  ASSERT_EQ(machine2.Readable("aba"), true);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("abababab"), true);
  ASSERT_EQ(machine2.Readable(""), true);
}

TEST(epsilon_transitions, test_5) {
  std::string input_file = "../tests/test_input/eps_tests/test5.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.Readable("a"), true);
  ASSERT_EQ(machine2.Readable("aba"), true);
  ASSERT_EQ(machine2.Readable(""), false);
  ASSERT_EQ(machine2.Readable("ab"), false);
  ASSERT_EQ(machine2.Readable("aaba"), true);
}

TEST(epsilon_transitions, test_6) {
  std::string input_file = "../tests/test_input/eps_tests/test6.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.Readable(""), true);
  ASSERT_EQ(machine2.Readable("abab"), true);
  ASSERT_EQ(machine2.Readable("b"), false);
}