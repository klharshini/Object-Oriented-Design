#pragma once
/////////////////////////////////////////////////////////////////////////
// Translater.h - Translates messages to/from managed and native types //
// ver 1.0                                                           //
// Author : Lakshmi Harshini Kuchibhotla,                            //
//          CSE687 - Object Oriented Design, Spring 2018             //
// Source : Jim Fawcett, CSE687 - Object Oriented Design             //
/////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
* ---------------------
*  This C++\Cli Package contains one class, Translater.  It's purpose is to convert
*  managed messages, CsMessage, to native messages, Message, and back.
*
*  Required Files:
* -----------------
*  Translater.h, Translater.cpp
*  CsMessage.h
*  Required References:
* ----------------------
*  CommLibWrapper.dll
*  Message.lib
*  TestUtilities.lib
*  
*
*  Maintenance History:
* ----------------------
*  ver 1.0 : 3/27/2018
*  - first release
*/

// Project > Properties > C/C++ > Language > Conformance mode set to No
// Add references to System, System.Core

#include <string>
#include "../CppCommWithFileXfer/MsgPassingComm/IComm.h"
#include "CsMessage.h"
#include "../CommLibWrapper/CommLibWrapper.h"
#include "../TestUtilities/TestRequest.h"

using namespace System;
using namespace System::Text;

namespace MsgPassingCommunication
{
  public ref class Translater
  {
  public:
    Translater();
    ~Translater();
    void listen(CsEndPoint^ ep);
    void postMessage(CsMessage^ msg);
    CsMessage^ getMessage();
	CsMessage ^ GetTestRequestMessage(String ^ Author, String ^ Name, List<String^>^ dllFiles);
    CsMessage^ fromMessage(Message& msg);
    Message fromCsMessage(CsMessage^ csMsg);
	void SetSendFileDirectory(String^ sendFileDir);
  private:
    CsEndPoint^ ep_;
    MsgPassingCommunication::CommFactory* pFactory;
    MsgPassingCommunication::IComm* pComm;
  };
  //----< initialize endpoint >----------------------------------------

  Translater::Translater()
  {
    ep_ = gcnew CsEndPoint;
  }
  inline Translater::~Translater()
  {
	  pComm->stop();
  }
  //----< set client listen endpoint and start Comm >------------------

  void Translater::listen(CsEndPoint^ ep)
  {
    std::cout << "\n  using CommFactory to create instance of Comm on native heap";
    ep_->machineAddress = ep->machineAddress;
    ep_->port = ep->port;
    pFactory = new CommFactory;
    pComm = pFactory->create(Sutils::MtoNstr(ep_->machineAddress), ep_->port);
    pComm->start();
    delete pFactory;
  }
  //----< convert native message to managed message >------------------

  CsMessage^ Translater::fromMessage(Message& msg)
  {
    CsMessage^ csMsg = gcnew CsMessage;
    Message::Attributes attribs = msg.attributes();
    for (auto attrib : attribs)
    {
      csMsg->add(Sutils::NtoMstr(attrib.first), Sutils::NtoMstr(attrib.second));
    }
    return csMsg;
  }
  //----< convert managed message to native message >------------------

  Message Translater::fromCsMessage(CsMessage^ csMsg)
  {
    Message msg;
    auto enumer = csMsg->attributes->GetEnumerator();
    while (enumer.MoveNext())
    {
      String^ key = enumer.Current.Key;
      String^ value = enumer.Current.Value;
      msg.attribute(Sutils::MtoNstr(key), Sutils::MtoNstr(value));
    }
    return msg;
  }
  inline void Translater::SetSendFileDirectory(String ^ sendFileDir)
  {
	  pComm->setSendFilePath(Sutils::MtoNstr(sendFileDir));
  }
  //----< use Comm to post message >-----------------------------------

  inline void Translater::postMessage(CsMessage^ csMsg)
  {
    std::cout << "\n  posting message in Translater";
    Message msg = this->fromCsMessage(csMsg);
    pComm->postMessage(msg);
  }
  //----< get message from Comm >--------------------------------------

  inline CsMessage^ Translater::getMessage()
  {
    std::cout << "\n  getting message in Translater";
    Message msg = pComm->getMessage();
    return fromMessage(msg);
  }

  inline CsMessage^ Translater::GetTestRequestMessage(String^ Author, String^ Name, List<String^>^ dllFiles)
  {
	  TestRequest testReq;
	  
	  std::string name = Sutils::MtoNstr(Name);
	  testReq.name(name);

	  std::string author = Sutils::MtoNstr(Author);
	  testReq.author(author);

	  Utilities::DateTime dt;
	  testReq.date(dt.now());

	  for each (String ^ file in dllFiles)
	  {
		  testReq.addDll(Sutils::MtoNstr(file));
	  }
	  Message testReqMsg;
	  testReqMsg.name(testReq.name());
	  testReqMsg.attribute("testRequest", testReq.toString());
	  return fromMessage(testReqMsg);
  }
}