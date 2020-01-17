/*

*/
import java.util.Set;
import java.util.HashSet;
import java.util.Arrays;
import java.lang.Math;

public class CSPZebra extends CSP {

    static Set<Object> varCol = new HashSet<Object>(
            Arrays.asList(new String[]{"green", "blue", "red", "ivory", "yellow"}));
    static Set<Object> varDri = new HashSet<Object>(
            Arrays.asList(new String[]{"coffee", "milk", "orange-juice", "tea", "water"}));
    static Set<Object> varNat = new HashSet<Object>(
            Arrays.asList(new String[]{"englishman", "japanese", "norwegian", "spaniard", "ukrainian"}));
    static Set<Object> varPet = new HashSet<Object>(
            Arrays.asList(new String[]{"dog", "fox", "horse", "snails", "zebra"}));
    static Set<Object> varCig = new HashSet<Object>(
            Arrays.asList(new String[]{"chesterfield", "kools", "lucky-strike", "old-gold", "parliament"}));

    public boolean isGood(Object X, Object Y, Object x, Object y) {
        if (!C.containsKey(X)) {
            return true;
        }

        if (!C.get(X).contains(Y)) {
            return true;
        }

        if (X.equals("englishman") && Y.equals("red") && !x.equals(y)) {
            return false;
        }

        if (X.equals("spaniard") && Y.equals("dog") && !x.equals(y)) {
            return false;
        }
        if (X.equals("coffee") && Y.equals("green") && !x.equals(y)) {
            return false;
        }
        if (X.equals("ukrainian") && Y.equals("tea") && !x.equals(y)) {
            return false;
        }
        if (X.equals("green") && Y.equals("ivory") && !((int) x - (int) y == 1)) {
            return false;
        }
        if (X.equals("old-gold") && Y.equals("snails") && !x.equals(y)) {
            return false;
        }
        if (X.equals("kools") && Y.equals("yellow") && !x.equals(y)) {
            return false;
        }
        if (X.equals("milk") && Y.equals(3) && !x.equals(y)) {
            return false;
        }
        if (X.equals("norwegian") && Y.equals(1) && !x.equals(y)) {
            return false;
        }
        if (X.equals("chesterfield") && Y.equals("fox") && !(Math.abs((int) x - (int) y) == 1)) {
            return false;
        }
        if (X.equals("kools") && Y.equals("horse") && !(Math.abs((int) x - (int) y) == 1)) {
            return false;
        }
        if (X.equals("lucky-strike") && Y.equals("orange-juice") && !x.equals(y)) {
            return false;
        }
        if (X.equals("japanese") && Y.equals("parliament") && !x.equals(y)) {
            return false;
        }
        if (X.equals("norwegian") && Y.equals("blue") && !(Math.abs((int) x - (int) y) == 1)) {
            return false;
        }

        if (varCol.contains(X) && varCol.contains(Y) && !X.equals(Y) && x.equals(y)) {
            return false;
        }

        if (varDri.contains(X) && varDri.contains(Y) && !X.equals(Y) && x.equals(y)) {
            return false;
        }
        if (varNat.contains(X) && varNat.contains(Y) && !X.equals(Y) && x.equals(y)) {
            return false;
        }
        if (varPet.contains(X) && varPet.contains(Y) && !X.equals(Y) && x.equals(y)) {
            return false;
        }
        if (varCig.contains(X) && varCig.contains(Y) && !X.equals(Y) && x.equals(y)) {
            return false;
        }

        return true;

    }

    public static void main(String[] args) throws Exception {
        CSPZebra csp = new CSPZebra();
        Integer[] dom = {1, 2, 3, 4, 5};
        Integer[] dom1 = {3};
        Integer[] dom2 = {1};

        for (Object color : varCol) {
            csp.addDomain(color, dom);
        }
        for (Object drink : varDri) {
            csp.addDomain(drink, dom);
        }

        for (Object nation : varNat) {
            csp.addDomain(nation, dom);
        }

        for (Object pet : varPet) {
            csp.addDomain(pet, dom);
        }

        for (Object cigarette : varCig) {
            csp.addDomain(cigarette, dom);
        }


        csp.addBidirectionalArc("englishman", "red");
        csp.addBidirectionalArc("spaniard", "dog");
        csp.addBidirectionalArc("coffee", "green");
        csp.addBidirectionalArc("ukrainian", "tea");
        csp.addBidirectionalArc("old-gold", "snails");
        csp.addBidirectionalArc("kools", "yellow");
        csp.addDomain("milk", new Integer[]{3});
        csp.addDomain("norwegian", new Integer[]{1});
        csp.addBidirectionalArc("chesterfield", "fox");
        csp.addBidirectionalArc("kools", "horse");
        csp.addBidirectionalArc("lucky-strike", "orange-juice");
        csp.addBidirectionalArc("japanese", "parliament");
        csp.addBidirectionalArc("norwegian", "blue");

        for (Object X : varCol) {
            for (Object Y : varCol) {
                csp.addBidirectionalArc(X, Y);
            }
        }
        for (Object X : varDri) {
            for (Object Y : varDri) {
                csp.addBidirectionalArc(X, Y);
            }
        }
        for (Object X : varNat) {
            for (Object Y : varNat) {
                csp.addBidirectionalArc(X, Y);
            }
        }
        for (Object X : varPet) {
            for (Object Y : varPet) {
                csp.addBidirectionalArc(X, Y);
            }
        }
        for (Object X : varCig) {
            for (Object Y : varCig) {
                csp.addBidirectionalArc(X, Y);
            }
        }
        Search search = new Search(csp);
        System.out.println(search.BacktrackingSearch());
    }

}
