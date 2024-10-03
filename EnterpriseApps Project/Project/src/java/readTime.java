
import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.sql.*;

/**
 *
 * @author matto
 */
public class readTime extends HttpServlet {
String name;
String time;

Connection conn;
Statement stat;
    
    public void init() throws ServletException {
        String url = "jdbc:mysql://localhost:3306/";
        String dbName = "appdev";
        String userName = "root";
        String password = "";
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = (Connection) DriverManager.getConnection(url + dbName, userName, password);
            stat = (Statement) conn.createStatement();
            System.out.println("Connected");
            
        } catch (Exception e) {
            System.err.println(e);
        }
    } // end of init() method


    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Statement stmt;
        // Set response content type 
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Database Result";
        String docType = "<!doctype html>";
        out.println(docType + "<html>\n"
                + "<head><title>" + title + "</title></head>\n"
                + "<h1 align=\"center\">" + title + "</h1>\n"
        );
        try {
            // Execute SQL query
            stmt = (Statement) conn.createStatement();
            String sql;
            sql = "SELECT * FROM time";
            ResultSet rs = stmt.executeQuery(sql);
            // Extract data from result set 
            while (rs.next()) {
                //Retrieve by column name
                String first = rs.getString("name");
                String last = rs.getString("time");
                //Display values
                out.println("Name: " + first);
                out.println("	Time: " + last + "<br>");
            }
  	out.println("<br> <br> <br> <a href=\"index.html\">Home</a>");
           out.println("</body></html>");
        } catch (Exception e) {
            e.printStackTrace();
        } //end try
    }


    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
