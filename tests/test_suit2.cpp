#include <gtest/gtest.h>
#include "../src/FiniteStateMachine.h"
#include "../src/DeterminedFiniteStateMachine.h"

TEST(dfsm, test_1) {
  std::string input_file = "../tests/test_input/DFSM_tests/test1.txt";
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
  ASSERT_EQ(machine2.Readable("abaa"), true);
  ASSERT_EQ(machine2.Readable("aaaa"), true);
  ASSERT_EQ(machine2.Readable("b"), false);
}

TEST(dfsm, test_2) {
  std::string input_file = "../tests/test_input/DFSM_tests/test2.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.size(), 3);
  ASSERT_EQ(machine2.Readable("aaa"), false);
  ASSERT_EQ(machine2.Readable("a"), true);
}

TEST(dfsm, test_3) {
  std::string input_file = "../tests/test_input/DFSM_tests/test3.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.size(), 3);
  ASSERT_EQ(machine2.Readable("b"), true);
  ASSERT_EQ(machine2.Readable("ba"), true);
  ASSERT_EQ(machine2.Readable("baaaaaa"), true);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("bab"), false);
}

TEST(dfsm, test_4) {
  std::string input_file = "../tests/test_input/DFSM_tests/test4.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.size(), 4);
  ASSERT_EQ(machine2.Readable("a"), true);
  ASSERT_EQ(machine2.Readable("ba"), false);
}

TEST(dfsm, test_5) {
  std::string input_file = "../tests/test_input/DFSM_tests/test5.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.size(), 8);
  ASSERT_EQ(machine2.Readable("b"), true);
  ASSERT_EQ(machine2.Readable("aaaaaaaaaaaaaa"), false);
  ASSERT_EQ(machine2.Readable(""), true);
  ASSERT_EQ(machine2.Readable("ba"), true);
  ASSERT_EQ(machine2.Readable("bab"), true);
  ASSERT_EQ(machine2.Readable("bba"), true);
  ASSERT_EQ(machine2.Readable("ab"), true);
  ASSERT_EQ(machine2.Readable("abba"), true);
  ASSERT_EQ(machine2.Readable("abab"), true);
  ASSERT_EQ(machine2.Readable("abbb"), false);
  ASSERT_EQ(machine2.Readable("abaa"), false);
  ASSERT_EQ(machine2.Readable("bb"), false);
}

TEST(dfsm, test_6) {
  std::string input_file = "../tests/test_input/DFSM_tests/test6.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.size(), 2);
  ASSERT_EQ(machine2.Readable("a"), true);
  ASSERT_EQ(machine2.Readable("aaaaaaaaaaaaaa"), true);
  ASSERT_EQ(machine2.Readable(""), true);
}

TEST(dfsm, test_7) {
  std::string input_file = "../tests/test_input/DFSM_tests/test7.txt";
  FiniteStateMachine machine;
  machine.EnterMachine(input_file);
  machine.GetRidOfEpsTransitions();
  DeterminedFiniteStateMachine machine2;
  machine2.EnterNSM(machine);
  machine2.MakeDFSM();
  machine2.MakeFull();
  ASSERT_EQ(machine2.size(), 3);
  ASSERT_EQ(machine2.Readable("a"), false);
  ASSERT_EQ(machine2.Readable("baaaaaaaaaaaaaa"), true);
  ASSERT_EQ(machine2.Readable(""), false);
  ASSERT_EQ(machine2.Readable("ba"), true);
  ASSERT_EQ(machine2.Readable("baab"), false);
}