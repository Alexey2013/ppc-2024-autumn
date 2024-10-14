// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "core/task/include/task.hpp"
#include "ref/most_different_neighbor_elements/include/ref_task.hpp"

TEST(most_different_neighbor_elements, check_int32_t) {
  // Create data
  std::vector<int32_t> in(1256, 1);
  std::vector<int32_t> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (size_t i = 0; i < in.size(); i++) {
    in[i] = 2 * i;
  }
  in[234] = 0;
  in[235] = 4000;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::MostDifferentNeighborElements<int32_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_EQ(out[0], 0);
  EXPECT_EQ(out[1], 4000);
  EXPECT_EQ(out_index[0], 234ull);
  EXPECT_EQ(out_index[1], 235ull);
}

TEST(most_different_neighbor_elements, check_validate_func) {
  // Create data
  std::vector<int32_t> in(125, 1);
  std::vector<int32_t> out(2, 0);
  std::vector<uint64_t> out_index(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::MostDifferentNeighborElements<int32_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, false);
}

TEST(most_different_neighbor_elements, check_double) {
  // Create data
  std::vector<double> in(25680, 1);
  std::vector<double> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (size_t i = 0; i < in.size(); i++) {
    in[i] = i;
  }
  in[189] = -1000.1;
  in[190] = 9000.9;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::MostDifferentNeighborElements<double, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_NEAR(out[0], -1000.1, 1e-6);
  EXPECT_NEAR(out[1], 9000.9, 1e-6);
  EXPECT_EQ(out_index[0], 189ull);
  EXPECT_EQ(out_index[1], 190ull);
}

TEST(most_different_neighbor_elements, check_int8_t) {
  // Create data
  std::vector<int8_t> in(250, -1);
  std::vector<int8_t> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (size_t i = 0; i < in.size(); i++) {
    if (i % 2 == 0) {
      in[i] = -50;
    } else {
      in[i] = 50;
    }
  }
  in[5] = 56;
  in[6] = -56;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::MostDifferentNeighborElements<int8_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_EQ(out[0], 56);
  EXPECT_EQ(out[1], -56);
  EXPECT_EQ(out_index[0], 5ull);
  EXPECT_EQ(out_index[1], 6ull);
}

TEST(most_different_neighbor_elements, check_int64_t) {
  // Create data
  std::vector<int64_t> in(75836, 1);
  std::vector<int64_t> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (size_t i = 0; i < in.size(); i++) {
    if (i % 3 == 0) {
      in[i] = 10;
    }
    if (i % 3 == 1) {
      in[i] = 30;
    }
    if (i % 3 == 2) {
      in[i] = 70;
    }
  }
  in[20] = -1000;
  in[21] = 1119;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::MostDifferentNeighborElements<int64_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_EQ(out[0], -1000);
  EXPECT_EQ(out[1], 1119);
  EXPECT_EQ(out_index[0], 20ull);
  EXPECT_EQ(out_index[1], 21ull);
}

TEST(most_different_neighbor_elements, check_float) {
  // Create data
  std::vector<float> in(20, 1.f);
  std::vector<float> out(2, 0.f);
  std::vector<uint64_t> out_index(2, 0);
  for (size_t i = 0; i < in.size(); i++) {
    in[i] += (i + 1.f) * 2.5f;
  }
  in[0] = 110.001f;
  in[1] = -990.0025f;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::MostDifferentNeighborElements<float, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_NEAR(out[0], 110.001f, 1e-4f);
  EXPECT_NEAR(out[1], -990.0025f, 1e-4f);
  EXPECT_EQ(out_index[0], 0ull);
  EXPECT_EQ(out_index[1], 1ull);
}
