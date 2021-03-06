#ifndef _MZ_NET_TRANSMITSOCKET_HPP_
#define _MZ_NET_TRANSMITSOCKET_HPP_

#include "Metazion/Net/NetInclude.hpp"

#include "Metazion/Net/Socket.hpp"
#include "Metazion/Net/SocketBuffer.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

class TransmitSocket : public Socket {
    MZ_DISALLOW_COPY_AND_ASSIGN(TransmitSocket)

    friend class TransmitStrategy;

protected:
    TransmitStrategy m_transmitStrategy;
    SocketBuffer m_socketBuffer;
    Host m_remoteHost;

    int64_t m_connectedTime{ 0 };
    int64_t m_disconnectedTime{ 0 };
    int64_t m_firstSendTime{ 0 };
    int64_t m_lastSendTime{ 0 };
    int64_t m_sendedBytes{ 0 };
    int64_t m_firstRecvTime{ 0 };
    int64_t m_lastRecvTime{ 0 };
    int64_t m_recvedBytes{ 0 };

public:
    TransmitSocket();

    virtual ~TransmitSocket();

    void Reset() override;

    void Prepare() override;

    bool IsAlive() const override final;

    bool KeepEnough() const override final;

    IoStrategy& TheIoStrategy() override final;

    void OnAttached() override final;

    void OnDetached() override final;

    void OnStart() override final;

    void OnStop() override final;

    void OnError(int error) override final;

    int Send(const void* data, int length);

    SocketBuffer& TheSocketBuffer();

    Host& GetRemoteHost();

    void SetRemoteHost(const Host& host);

protected:
    virtual void OnConnected();

    virtual void OnDisconnected();

    virtual void OnSended(const void* data, int length);

    virtual void OnRecved(const void* data, int length);
};

inline IoStrategy& TransmitSocket::TheIoStrategy() {
    return m_transmitStrategy;
}

inline SocketBuffer& TransmitSocket::TheSocketBuffer() {
    return m_socketBuffer;
}

inline Host& TransmitSocket::GetRemoteHost() {
    return m_remoteHost;
}

inline void TransmitSocket::SetRemoteHost(const Host& host) {
    m_remoteHost = host;
}

DECL_NAMESPACE_MZ_NET_END

#endif // _MZ_NET_TRANSMITSOCKET_HPP_
