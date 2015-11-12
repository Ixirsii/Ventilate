#include "peerparser.h"

PeerParser::PeerParser()
{

}


void PeerParser::sendList(const ConnectionHandler& handler)
{
    QString list = server.serializePeerList();
    handler.write(list);
}

