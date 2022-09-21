// Copyright 2013 Google Inc. All Rights Reserved.

#include <gtest/gtest.h>

#include "file_store.h"
#include "test_vectors.h"

namespace wvcdm {

namespace {
const std::string kTestDirName = "test_dir";
const std::string kTestFileName = "test.txt";
const std::string kTestFileName2 = "test2.txt";
const std::string kTestFileNameExt = ".txt";
const std::string kWildcard = "*";
}  // namespace

class FileTest : public testing::Test {
 protected:
  FileTest() {}

  virtual void TearDown() { RemoveTestDir(); }

  void RemoveTestDir() {
    EXPECT_TRUE(file_system.Remove(test_vectors::kTestDir));
  }

  std::string GenerateRandomData(uint32_t len) {
    std::string data(len, 0);
    for (size_t i = 0; i < len; i++) {
      data[i] = rand() % 256;
    }
    return data;
  }

  FileSystem file_system;
};

TEST_F(FileTest, FileExists) {
  EXPECT_TRUE(file_system.Exists(test_vectors::kExistentFile));
  EXPECT_TRUE(file_system.Exists(test_vectors::kExistentDir));
  EXPECT_FALSE(file_system.Exists(test_vectors::kNonExistentFile));
  EXPECT_FALSE(file_system.Exists(test_vectors::kNonExistentDir));
}

TEST_F(FileTest, RemoveDir) {
  EXPECT_TRUE(file_system.Remove(test_vectors::kTestDir));
  EXPECT_FALSE(file_system.Exists(test_vectors::kTestDir));
}

TEST_F(FileTest, OpenFile) {
  std::string path = test_vectors::kTestDir + kTestFileName;
  EXPECT_TRUE(file_system.Remove(path));

  File* file = file_system.Open(path, FileSystem::kCreate);
  ASSERT_TRUE(file);
  file->Close();

  EXPECT_TRUE(file_system.Exists(path));
}

TEST_F(FileTest, RemoveDirAndFile) {
  std::string path = test_vectors::kTestDir + kTestFileName;

  File* file = file_system.Open(path, FileSystem::kCreate);
  ASSERT_TRUE(file);
  file->Close();

  EXPECT_TRUE(file_system.Exists(path));
  EXPECT_TRUE(file_system.Remove(path));
  EXPECT_FALSE(file_system.Exists(path));

  file = file_system.Open(path, FileSystem::kCreate);
  ASSERT_TRUE(file);
  file->Close();

  EXPECT_TRUE(file_system.Exists(path));
  RemoveTestDir();
  EXPECT_FALSE(file_system.Exists(test_vectors::kTestDir));
  EXPECT_FALSE(file_system.Exists(path));
}

TEST_F(FileTest, RemoveWildcardFiles) {
  std::string path1 = test_vectors::kTestDir + kTestFileName;
  std::string path2 = test_vectors::kTestDir + kTestFileName2;
  std::string wildcard_path =
      test_vectors::kTestDir + kWildcard + kTestFileNameExt;

  File* file = file_system.Open(path1, FileSystem::kCreate);
  ASSERT_TRUE(file);
  file->Close();
  file = file_system.Open(path2, FileSystem::kCreate);
  ASSERT_TRUE(file);
  file->Close();

  EXPECT_TRUE(file_system.Exists(path1));
  EXPECT_TRUE(file_system.Exists(path2));
  EXPECT_TRUE(file_system.Remove(wildcard_path));
  EXPECT_FALSE(file_system.Exists(path1));
  EXPECT_FALSE(file_system.Exists(path2));
}

TEST_F(FileTest, FileSize) {
  std::string path = test_vectors::kTestDir + kTestFileName;
  file_system.Remove(path);

  std::string write_data = GenerateRandomData(600);
  File* file = file_system.Open(path, FileSystem::kCreate);
  ASSERT_TRUE(file);
  EXPECT_TRUE(file->Write(write_data.data(), write_data.size()));
  file->Close();
  EXPECT_TRUE(file_system.Exists(path));

  EXPECT_EQ(static_cast<ssize_t>(write_data.size()),
            file_system.FileSize(path));
}

TEST_F(FileTest, WriteReadBinaryFile) {
  std::string path = test_vectors::kTestDir + kTestFileName;
  file_system.Remove(path);

  std::string write_data = GenerateRandomData(600);
  File* file = file_system.Open(path, FileSystem::kCreate);
  ASSERT_TRUE(file);
  EXPECT_TRUE(file->Write(write_data.data(), write_data.size()));
  file->Close();
  EXPECT_TRUE(file_system.Exists(path));

  std::string read_data;
  read_data.resize(file_system.FileSize(path));
  file = file_system.Open(path, FileSystem::kReadOnly);
  ASSERT_TRUE(file);
  EXPECT_TRUE(file->Read(&read_data[0], read_data.size()));
  file->Close();
  EXPECT_EQ(write_data, read_data);
}

}  // namespace wvcdm
