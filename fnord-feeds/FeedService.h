/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_FEEDS_H
#define _FNORD_FEEDS_H
#include <mutex>
#include <stdlib.h>
#include <set>
#include <string>
#include <unordered_map>
#include "fnord/base/io/filerepository.h"
#include "fnord-feeds/LocalFeed.h"
#include "fnord-feeds/FeedEntry.h"
#include "fnord/reflect/reflect.h"

namespace fnord {
namespace feeds {

class FeedService {
  friend class LogStream;
public:
  FeedService(
      fnord::FileRepository file_repo,
      const String& stats_path = "/feeds");

  /**
   * Append an entry to the stream referenced by `stream` and return the offset
   * at which the entry was written. Will create a new stream if the referenced
   * stream does not exist yet.
   *
   * @param stream the name/key of the stream to append to
   * @param entry the entry to append to the stream
   * @return the offset at which the entry was written
   */
  uint64_t append(std::string stream, std::string entry);

  /**
   * Read one or more entries from the stream at or after the provided start
   * offset. If the start offset references a deleted/expired entry, the next
   * valid entry will be returned. It is always valid to call this method with
   * a start offset of zero to retrieve the first entry or entries from the
   * stream.
   *
   * The provided callback must return a boolean. If the callback returns true,
   * the next entry will be read (if there is a next entry). If the callback
   * returns false the scan method will return.
   *
   * @param start_offset the start offset to read from
   */
  std::vector<FeedEntry> fetch(
      std::string stream,
      uint64_t offset,
      int batch_size);

protected:
  String stats_path_;

  LogStream* openStream(const std::string& name, bool create);
  void reopenTable(const std::string& file_path);

  fnord::FileRepository file_repo_;
  std::unordered_map<std::string, std::unique_ptr<LogStream>> streams_;
  std::mutex streams_mutex_;
};

} // namespace logstream_service
} // namespace fnord

template <> template <class T>
void fnord::reflect::MetaClass<
    fnord::feeds::FeedService>::reflect(T* t) {
  t->method(
      "FeedService.append",
      &fnord::feeds::FeedService::append,
      "stream",
      "entry");

  t->method(
      "FeedService.fetch",
      &fnord::feeds::FeedService::fetch,
      "stream",
      "offset",
      "batch_size");
}

#endif