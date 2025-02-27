/*
 *  Copyright (C) 2020-2021 GrammaTech, Inc.
 *
 *  This code is licensed under the MIT license. See the LICENSE file in the
 *  project root for license terms.
 *
 *  This project is sponsored by the Office of Naval Research, One Liberty
 *  Center, 875 N. Randolph Street, Arlington, VA 22203 under contract #
 *  N68335-17-C-0700.  The content of the information does not necessarily
 *  reflect the position or policy of the Government and no official
 *  endorsement should be inferred.
 *
 */

package com.grammatech.gtirb.AuxSerialization;

/**
 * This class is a blob of bytes representing data with an unknown type.
 * Generated by Serialization.decode when it encounters the name of an
 * unknown codec. Use only at the top level of an auxdata.
 */
public class UnknownData {
    public byte[] bytes;
    public UnknownData(byte[] bytes) { this.bytes = bytes; }
}
