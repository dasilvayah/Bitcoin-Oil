Shared Libraries
================

## bitcoinoilconsensus

The purpose of this library is to make the verification functionality that is critical to BitcoinOil's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `bitcoinoilconsensus.h` located in  `src/script/bitcoinoilconsensus.h`.

#### Version

`bitcoinoilconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`bitcoinoilconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `bitcoinoilconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `bitcoinoilconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `bitcoinoilconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/bitcoinoil/bips/blob/master/bip-0016.mediawiki)) subscripts
- `bitcoinoilconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/bitcoinoil/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `bitcoinoilconsensus_ERR_OK` - No errors with input parameters *(see the return value of `bitcoinoilconsensus_verify_script` for the verification status)*
- `bitcoinoilconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `bitcoinoilconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `bitcoinoilconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NBitcoinOil](https://github.com/NicolasDorier/NBitcoinOil/blob/master/NBitcoinOil/Script.cs#L814) (.NET Bindings)
- [node-libbitcoinoilconsensus](https://github.com/bitpay/node-libbitcoinoilconsensus) (Node.js Bindings)
- [java-libbitcoinoilconsensus](https://github.com/dexX7/java-libbitcoinoilconsensus) (Java Bindings)
- [bitcoinoilconsensus-php](https://github.com/Bit-Wasp/bitcoinoilconsensus-php) (PHP Bindings)
