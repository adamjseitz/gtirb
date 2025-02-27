import com.grammatech.gtirb.AuxData;
import com.grammatech.gtirb.AuxSerialization.AuxDataSerialization;
import com.grammatech.gtirb.IR;
import com.grammatech.gtirb.Module;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.List;
import java.util.Map;

public class testAuxData {
    private static void serializeSelf(String type, Object value) {
        byte[] raw = AuxDataSerialization.encode(value, type);
        Object next = AuxDataSerialization.decode(raw, type);

        assert (value.equals(next));
    }

    public static void testSerialization() {
        serializeSelf("float", new Float(0.4));
        serializeSelf("double", new Double(1.0));
        serializeSelf("bool", new Boolean(true));
    }

    public static boolean testAuxDataDecodeEncode(IR ir) {
        List<Module> modules = ir.getModules();
        Module m = modules.get(0);
        if (m.getName().length() > 0) {
            System.out.println("Module " + m.getName());
        } else {
            System.out.println("Module has no name.");
        }
        Map<String, AuxData> auxDataMap = m.getAuxDataMap();
        AuxData auxData1 = auxDataMap.get("SCCs");
        Object object =
            AuxDataSerialization.decode(auxData1.getData(), auxData1.getType());
        if (object instanceof Map<?, ?>) {
            Map<?, ?> map = (Map<?, ?>)object;
            System.out.println("Map size " + map.size());
            byte[] rawBytes =
                AuxDataSerialization.encode(object, auxData1.getType());
            AuxData auxData2 =
                new AuxData(rawBytes, "newSCCs", auxData1.getType());
            auxDataMap.put("newSCCs", auxData2);
        } else
            return false;
        return true;
    }

    public static void main(String[] args) {

        if (args.length < 1) {
            System.err.println("No GTIRB file specified.");
            System.err.println("test failed.");
            System.exit(1);
            return;
        }

        InputStream inputStream;
        boolean loadReturned = false;
        IR ir = null;
        String fileName = args[0];
        File inputFile = new File(fileName);
        try {
            inputStream = new FileInputStream(inputFile);
            ir = IR.loadFile(inputStream);
            loadReturned = (ir == null);
            if (ir == null) {
                loadReturned = false;
            } else {
                loadReturned = true;
            }
            inputStream.close();
        } catch (Exception e) {
            System.out.println("Unable to parse " + fileName + "." + e);
            System.err.println("test failed.");
            System.exit(1);
        }

        if (loadReturned != true) {
            System.out.println("Unable to load " + fileName + ".");
            System.err.println("test failed.");
            System.exit(1);
        }

        if (testAuxDataDecodeEncode(ir)) {
            System.out.println("AuxData Test OK.");
        } else {
            System.err.println("AuxData test failed.");
            System.exit(1);
        }

        testSerialization();
    }
}
