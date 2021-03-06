#ifndef ZFLYEMBOOKMARK_H
#define ZFLYEMBOOKMARK_H

#include <QString>
#include "zintpoint.h"
#include "tz_stdint.h"
#include "zstackball.h"

class ZJsonObject;

class ZFlyEmBookmark : public ZStackBall
{
public:
  ZFlyEmBookmark();

  enum EBookmarkType {
    TYPE_FALSE_MERGE, TYPE_FALSE_SPLIT, TYPE_LOCATION
  };

  void display(ZPainter &painter, int slice, EDisplayStyle option) const;

  inline uint64_t getBodyId() const { return m_bodyId; }
  inline const QString& getTime() const { return m_time; }
  inline const QString& getUserName() const { return m_userName; }
  inline const QString& getStatus() const { return m_status; }
  inline const QString& getComment() const { return m_comment; }
  inline ZIntPoint getLocation() const { return getCenter().toIntPoint(); }
  inline EBookmarkType getBookmarkType() const { return m_bookmarkType; }
  inline void setBookmarkType(EBookmarkType type) { m_bookmarkType = type; }
  inline void setComment(const QString &comment) { m_comment = comment; }
  inline void setUser(const QString &user) { m_userName = user; }
  inline void setStatus(const QString &status) { m_status = status; }

  inline void setBodyId(uint64_t bodyId) { m_bodyId = bodyId; }
  inline void setLocation(int x, int y, int z) {
//    m_location.set(x, y, z);
    setCenter(x, y, z);
  }

  bool isChecked() const {
    return m_isChecked;
  }

  bool isCustom() const {
    return m_isCustom;
  }

  void setChecked(bool checked) {
    m_isChecked = checked;
  }

  QString getDvidKey() const;

  ZJsonObject toJsonObject(bool ignoringComment = false) const;
  void loadJsonObject(const ZJsonObject &jsonObj);

  void print() const;

  void setCustom(bool state);

  virtual const std::string& className() const;

  void clear();

private:
  uint64_t m_bodyId;
  QString m_userName;
  QString m_time;
  QString m_status;
  QString m_comment;
//  ZIntPoint m_location;
  EBookmarkType m_bookmarkType;
  bool m_isChecked;
  bool m_isCustom;
//  QString m_decorationText;
};

#endif // ZFLYEMBOOKMARK_H
