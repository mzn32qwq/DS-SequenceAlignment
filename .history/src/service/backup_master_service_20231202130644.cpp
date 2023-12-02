#include "service/backup_master_service.h"

void BackupMasterService::onInit() {}

void BackupMasterService::onNewMessage(std::string peer_id,
                                       const std::string& message, bool is_binary) {}

std::string BackupMasterService::onConnectionEstablished(const std::string& peer_id) {
    mtx.
}

void BackupMasterService::onConnectionTerminated(const std::string& peer_id) {}
