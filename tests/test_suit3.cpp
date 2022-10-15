#include <gtest/gtest.h>
#include "../src/FiniteStateMachine.h"
#include "../src/DeterminedFiniteStateMachine.h"

TEST(addition, test_1) {
  std::string input_file = "../tests/test_input/add_tests/test1.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  machine2.MakeAddition();
  ASSERT_EQ(machine2.Readable(""), true);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("b"), true);
  ASSERT_EQ(machine2.Readable("ab"), true);
  ASSERT_EQ(machine2.Readable("aa"), true);
  ASSERT_EQ(machine2.Readable("bb"), true);
  ASSERT_EQ(machine2.Readable("ba"), true);
}

TEST(addition, test_2) {
  std::string input_file = "../tests/test_input/add_tests/test2.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  machine2.MakeAddition();
  ASSERT_EQ(machine2.Readable(""), false);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("aa"), false);
}

TEST(addition, test_3) {
  std::string input_file = "../tests/test_input/add_tests/test3.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  machine2.MakeAddition();
  ASSERT_EQ(machine2.Readable(""), false);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("aa"), false);
  ASSERT_EQ(machine2.Readable("b"), true);
  ASSERT_EQ(machine2.Readable("ab"), true);
  ASSERT_EQ(machine2.Readable("bb"), true);
  ASSERT_EQ(machine2.Readable("ba"), true);
}