/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "FileItem.h"
#include "filesystem/StackDirectory.h"
#include "network/NetworkFileItemClassify.h"

#include <array>
#include <string>

#include <gtest/gtest.h>

using namespace KODI;

struct InternetStreamDefinition
{
  InternetStreamDefinition(const std::string& path, bool folder, bool strict, bool res)
    : item(path, folder), strictCheck(strict), result(res)
  {
  }

  CFileItem item;
  bool strictCheck;
  bool result;
};

class InternetStreamTest : public testing::WithParamInterface<InternetStreamDefinition>,
                           public testing::Test
{
};

TEST_P(InternetStreamTest, IsInternetStream)
{
  EXPECT_EQ(NETWORK::IsInternetStream(GetParam().item, GetParam().strictCheck), GetParam().result);
}

const auto inetstream_tests = std::array{
    InternetStreamDefinition{"/home/user/test.disc", false, false, false},
    InternetStreamDefinition{"/home/user/test.disc", true, true, false},
    InternetStreamDefinition{"http://some.where/foo", false, false, true},
    InternetStreamDefinition{"http://some.where/foo", false, true, true},
    InternetStreamDefinition{"http://some.where/foo", true, false, true},
    InternetStreamDefinition{"http://some.where/foo", true, true, true},
    InternetStreamDefinition{"https://some.where/foo", false, false, true},
    InternetStreamDefinition{"https://some.where/foo", false, true, true},
    InternetStreamDefinition{"https://some.where/foo", true, false, true},
    InternetStreamDefinition{"https://some.where/foo", true, true, true},
    InternetStreamDefinition{"tcp://some.where/foo", false, false, true},
    InternetStreamDefinition{"tcp://some.where/foo", false, true, true},
    InternetStreamDefinition{"tcp://some.where/foo", true, false, true},
    InternetStreamDefinition{"tcp://some.where/foo", true, true, true},
    InternetStreamDefinition{"udp://some.where/foo", false, false, true},
    InternetStreamDefinition{"udp://some.where/foo", false, true, true},
    InternetStreamDefinition{"udp://some.where/foo", true, false, true},
    InternetStreamDefinition{"udp://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtp://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtp://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtp://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtp://some.where/foo", true, true, true},
    InternetStreamDefinition{"sdp://some.where/foo", false, false, true},
    InternetStreamDefinition{"sdp://some.where/foo", false, true, true},
    InternetStreamDefinition{"sdp://some.where/foo", true, false, true},
    InternetStreamDefinition{"sdp://some.where/foo", true, true, true},
    InternetStreamDefinition{"mms://some.where/foo", false, false, true},
    InternetStreamDefinition{"mms://some.where/foo", false, true, true},
    InternetStreamDefinition{"mms://some.where/foo", true, false, true},
    InternetStreamDefinition{"mms://some.where/foo", true, true, true},
    InternetStreamDefinition{"mmst://some.where/foo", false, false, true},
    InternetStreamDefinition{"mmst://some.where/foo", false, true, true},
    InternetStreamDefinition{"mmst://some.where/foo", true, false, true},
    InternetStreamDefinition{"mmst://some.where/foo", true, true, true},
    InternetStreamDefinition{"mmsh://some.where/foo", false, false, true},
    InternetStreamDefinition{"mmsh://some.where/foo", false, true, true},
    InternetStreamDefinition{"mmsh://some.where/foo", true, false, true},
    InternetStreamDefinition{"mmsh://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtsp://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtsp://some.where/foo", false, true, true},
    InternetStreamDefinition{"rtsp://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtsp://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtmp://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtmp://some.where/foo", false, true, true},
    InternetStreamDefinition{"rtmp://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtmp://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtmpt://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtmpt://some.where/foo", false, true, true},
    InternetStreamDefinition{"rtmpt://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtmpt://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtmpe://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtmpe://some.where/foo", false, true, true},
    InternetStreamDefinition{"rtmpe://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtmpe://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtmpte://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtmpte://some.where/foo", false, true, true},
    InternetStreamDefinition{"rtmpte://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtmpte://some.where/foo", true, true, true},
    InternetStreamDefinition{"rtmps://some.where/foo", false, false, true},
    InternetStreamDefinition{"rtmps://some.where/foo", false, true, true},
    InternetStreamDefinition{"rtmps://some.where/foo", true, false, true},
    InternetStreamDefinition{"rtmps://some.where/foo", true, true, true},
    InternetStreamDefinition{"shout://some.where/foo", false, false, true},
    InternetStreamDefinition{"shout://some.where/foo", false, true, true},
    InternetStreamDefinition{"shout://some.where/foo", true, false, true},
    InternetStreamDefinition{"shout://some.where/foo", true, true, true},
    InternetStreamDefinition{"rss://some.where/foo", false, false, true},
    InternetStreamDefinition{"rss://some.where/foo", false, true, true},
    InternetStreamDefinition{"rss://some.where/foo", true, false, true},
    InternetStreamDefinition{"rss://some.where/foo", true, true, true},
    InternetStreamDefinition{"rsss://some.where/foo", false, false, true},
    InternetStreamDefinition{"rsss://some.where/foo", false, true, true},
    InternetStreamDefinition{"rsss://some.where/foo", true, false, true},
    InternetStreamDefinition{"rsss://some.where/foo", true, true, true},
    InternetStreamDefinition{"upnp://some.where/foo", false, false, false},
    InternetStreamDefinition{"upnp://some.where/foo", true, false, false},
    InternetStreamDefinition{"upnp://some.where/foo", false, true, true},
    InternetStreamDefinition{"upnp://some.where/foo", true, true, true},
    InternetStreamDefinition{"ftp://some.where/foo", false, false, false},
    InternetStreamDefinition{"ftp://some.where/foo", true, false, false},
    InternetStreamDefinition{"ftp://some.where/foo", false, true, true},
    InternetStreamDefinition{"ftp://some.where/foo", true, true, true},
    InternetStreamDefinition{"sftp://some.where/foo", false, false, false},
    InternetStreamDefinition{"sftp://some.where/foo", true, false, false},
    InternetStreamDefinition{"sftp://some.where/foo", false, true, true},
    InternetStreamDefinition{"sftp://some.where/foo", true, true, true},
    InternetStreamDefinition{"ssh://some.where/foo", false, false, false},
    InternetStreamDefinition{"ssh://some.where/foo", true, false, false},
    InternetStreamDefinition{"ssh://some.where/foo", false, true, true},
    InternetStreamDefinition{"ssh://some.where/foo", true, true, true},
    InternetStreamDefinition{"ssh://some.where/foo", true, true, true},
};

INSTANTIATE_TEST_SUITE_P(TestNetworkFileItemClassify,
                         InternetStreamTest,
                         testing::ValuesIn(inetstream_tests));

TEST(TestNetworkWorkFileItemClassify, InternetStreamStacks)
{
  std::string stackPath;
  EXPECT_TRUE(XFILE::CStackDirectory::ConstructStackPath(
      {"/home/foo/somthing.avi", "/home/bar/else.mkv"}, stackPath));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, false), false));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, true), false));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, false), true));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, true), true));

  EXPECT_TRUE(XFILE::CStackDirectory::ConstructStackPath(
      {"https://home/foo/somthing.avi", "https://home/bar/else.mkv"}, stackPath));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, false), false));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, true), false));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, false), true));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, true), true));

  EXPECT_TRUE(XFILE::CStackDirectory::ConstructStackPath(
      {"ftp://home/foo/somthing.avi", "ftp://home/bar/else.mkv"}, stackPath));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, false), false));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, true), false));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, false), true));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, true), true));

  EXPECT_TRUE(XFILE::CStackDirectory::ConstructStackPath(
      {"ftp://home/foo/somthing.avi", "/home/bar/else.mkv"}, stackPath));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, false), false));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, true), false));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, false), true));
  EXPECT_TRUE(NETWORK::IsInternetStream(CFileItem(stackPath, true), true));

  EXPECT_TRUE(XFILE::CStackDirectory::ConstructStackPath(
      {"/home/foo/somthing.avi", "ftp://home/bar/else.mkv"}, stackPath));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, false), false));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, true), false));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, false), true));
  EXPECT_FALSE(NETWORK::IsInternetStream(CFileItem(stackPath, true), true));
}
