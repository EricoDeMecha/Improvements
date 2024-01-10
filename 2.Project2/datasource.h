#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "joke.h"

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

    Q_INVOKABLE void fetchJokes( int number);

    void addJoke(Joke * joke);

    Q_INVOKABLE void addJoke();

    Q_INVOKABLE void addJoke(const QString & jokeParam);

    Q_INVOKABLE void removeJoke(int index);

    Q_INVOKABLE void removeLastJoke();

    QList<Joke *> dataItems();


signals:
    void preItemAdded();
    void postItemAdded();
    void preItemRemoved(int index);
    void postItemRemoved();

    void requestCompleted();
private slots:
    void dataReadyRead();
    void dataReadFinished();

    void makeRequest();
public slots:
private :
    QNetworkAccessManager * mNetManager;
    QNetworkReply * mNetReply;
    QByteArray * mDataBuffer;
    QList<Joke*> mJokes;

    typedef enum : unsigned int {
        REQUESTS_ONGOING = 0,
        REQUESTS_COMPLETED,
    }RequestsState;

    RequestsState mRequestState{REQUESTS_COMPLETED};
    int mRequestsToMake{0};
};

#endif // DATASOURCE_H
