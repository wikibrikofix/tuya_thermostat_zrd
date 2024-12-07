const {identify, reporting, ota} = require('zigbee-herdsman-converters/lib/modernExtend');

const definition = {
    fingerprint: [{modelID: 'TS0601', manufacturerName: '_TZE204_u9bfwha0'}],
    zigbeeModel: ['TS0601'],
    model: 'TS0601',
    vendor: '_TZE204_u9bfwha0',
    description: 'Automatically generated definition',
    extend: [
      identify(),
      ota(),
    ],
    meta: {},
};

module.exports = definition;