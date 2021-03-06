#ifndef ZDVIDBUFFERREADER_H
#define ZDVIDBUFFERREADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QEventLoop>
#include <QString>
#include <QNetworkReply>

class QTimer;

/*!
 * \brief The class of reading dvid data into buffer
 */
class ZDvidBufferReader : public QObject
{
  Q_OBJECT
public:
  explicit ZDvidBufferReader(QObject *parent = 0);

  enum EStatus {
    READ_NULL, READ_OK, READ_FAILED, READ_TIMEOUT, READ_CANCELED,
    READ_BAD_RESPONSE
  };

  void read(const QString &url, bool outputUrl = true);
  void readHead(const QString &url);
  bool isReadable(const QString &url);
  bool hasHead(const QString &url);

  EStatus getStatus() const;

  inline const QByteArray& getBuffer() const {
    return m_buffer;
  }

  void readQt(const QString &url, bool outputUrl = true);

signals:
  void readingDone();
  void readingCanceled();
  void checkingStatus();

public slots:

private slots:
  void handleError(QNetworkReply::NetworkError error);
  void finishReading();
  void handleTimeout();
  void cancelReading();
  void readBuffer();
  void waitForReading();

private:
  void startReading();
  void endReading(EStatus status);


  bool isReadingDone() const;

private:
  QByteArray m_buffer;
  QNetworkAccessManager *m_networkManager;
  QNetworkReply *m_networkReply;
  QEventLoop *m_eventLoop;
  bool m_isReadingDone;
  EStatus m_status;
//  QTimer *m_timer;
};

#endif // ZDVIDBUFFERREADER_H
